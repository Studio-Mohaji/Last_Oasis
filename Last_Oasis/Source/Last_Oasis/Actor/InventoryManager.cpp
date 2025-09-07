// Fill out your copyright notice in the Description page of Project Settings.


#include "../Actor/InventoryManager.h"
#include "../Actor/CraftingManager.h"

#include "Actor/InteractiveActor.h"
#include "Character/PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"

AInventoryManager::AInventoryManager()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AInventoryManager::BeginPlay()
{
	Super::BeginPlay();

    CraftingManager = Cast<ACraftingManager>(
        UGameplayStatics::GetActorOfClass(GetWorld(), ACraftingManager::StaticClass()));

    UE_LOG(LogTemp, Warning, TEXT("BeginPlay RecipeItems.Num = %d"), RecipeItems.Num());
}

void AInventoryManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AInventoryManager::UseItem(UDataAssetBase* ItemData)
{
	if (!ItemData) return;
	
    CheckRecipe(ItemData);

    for (int32 i = 0; i < ItemDataList.Num(); i++)
    {
        FInventoryItem& item = ItemDataList[i];
        if (item.ItemData == ItemData && ItemData->IsUsable)
        {
            if (item.CurrentCount > 0)
            {
                UE_LOG(LogTemp, Warning, TEXT("Use Item"));

                APlayerCharacter* PC = Cast<APlayerCharacter>(
                    UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

                if (PC && ItemData->UseValue != 0.f)
                {
                    if (ItemData == UsableItemDatas[2]) // ����
                        PC->InputPressed(2);
                    else if (ItemData == UsableItemDatas[3]) // ��
                        PC->InputPressed(3);
                    else if (ItemData == UsableItemDatas[4]) // �ش�
                        PC->InputPressed(4);
                }


                item.CurrentCount--;

                if (item.CurrentCount <= 0)
                {
                    ItemDataList.RemoveAt(i);
                }
            }
            return;
        }
    }

}


void AInventoryManager::GetItem(AInteractiveActor* InteractiveActor)
{
    if (!InteractiveActor) return;

    GetDropItemData(InteractiveActor->DropItems);
}

void AInventoryManager::GetDropItemData(const TArray<FDropItemData>& AcquiredItemData)
{
	if (AcquiredItemData.Num() <= 0) return;

    for (const FDropItemData& DropData : AcquiredItemData)
    {
        if (!DropData.DropItemData) continue;

        int32 RandomRoll = FMath::RandRange(1, 100);
        if (RandomRoll > DropData.DropChance) // ȹ�� ����
        {
            UE_LOG(LogTemp, Warning, TEXT("Item drop chance failed)"));
            continue;
        }

        // ��� ����
        int32 DropCount = FMath::RandRange(DropData.DropMinRange, DropData.DropMaxRange);

        UE_LOG(LogTemp, Warning, TEXT("drop Count %d)"), DropCount);
        // ������ ȹ��
        for (int32 i = 0; i < DropCount; i++)
        {
            UDataAssetBase* ItemData = DropData.DropItemData;
            if (!ItemData) continue;

            bool bItemFound = false;

            for (int32 j = 0; j < ItemDataList.Num(); j++)
            {
                FInventoryItem& item = ItemDataList[j];

                if (item.ItemData == ItemData)
                {
                    bItemFound = true;

                    if (item.ItemData->IsStackable)
                    {
                        if (item.CurrentCount < item.ItemData->MaxStackCount)
                        {
                            item.CurrentCount++;
                            UE_LOG(LogTemp, Warning, TEXT("Added stack of item: %s"), *ItemData->ItemName.ToString());
                            UpdateBroadCast();
                        }
                    }
                    else
                    {
                        UE_LOG(LogTemp, Warning, TEXT("You can't have duplicated item: %s"), *ItemData->ItemName.ToString());
                    }
                    break;
                }
            }

            // ���� �κ��丮�� ���� �������̶�� ���� �߰�
            if (!bItemFound)
            {
                FInventoryItem NewItem;
                NewItem.ItemData = ItemData;
                NewItem.CurrentCount = 1;
                ItemDataList.Add(NewItem);

                UE_LOG(LogTemp, Warning, TEXT("New item added to inventory: %s"), *ItemData->ItemName.ToString());

                UpdateBroadCast();
            }
        }
    }
}



void AInventoryManager::TestGetItem()
{
    bool bItemFound = false;
    for (int32 i = 0; i < ItemDataList.Num(); i++)
    {
        FInventoryItem& item = ItemDataList[i];
        if (item.ItemData == TestItemData)
        {
            bItemFound = true;
            if (item.ItemData->IsStackable)
            {
                if (item.CurrentCount <= item.ItemData->MaxStackCount)
                {
                    UE_LOG(LogTemp, Warning, TEXT("get Item"));

                    // ������ ȹ�� ȿ��
                    
                    item.CurrentCount++;
                    UpdateBroadCast();
                    return;
                }
            }
            else
            {
                UE_LOG(LogTemp, Warning, TEXT("You can't have duplicated item."))
                    return;
            }
        }
    }

    // ���� �κ��丮�� ���� �������̶�� ���� �߰�
    if (!bItemFound)
    {
        FInventoryItem NewItem;
        NewItem.ItemData = TestItemData;
        NewItem.CurrentCount = 1;
        ItemDataList.Add(NewItem);

        UpdateBroadCast();
    }
}

void AInventoryManager::CheckRecipe(UDataAssetBase* ItemData)
{

    for (int32 i = RecipeItems.Num() - 1; i >= 0; --i) // �ڿ��� ������ �ݺ��ϸ� RemoveAt ����
    {
        FRecipeUnlockedStruct& Recipe = RecipeItems[i];

        // ����� �������� �ش� �������� ���� ���������� üũ
        if (ItemData == Recipe.BlueprintItemData)
        {
            //  ������ �����Ϳ� RecipeState ����
            for (FRecipeState& RecipeState : CraftingManager->RecipeStates)
            {
                if (RecipeState.RecipeItem == Recipe.ItemData)
                {
                    RecipeState.bUnlocked = true; // �ر�
                    break;
                }
            }

            // CraftingWidget�� UI ������Ʈ ��û
            UpdateRecipeBroadCast();

            // ����� ������ ����
            //RecipeItems.RemoveAt(i);
        }
    }
}

void AInventoryManager::UpdateBroadCast()
{
    OnInventoryUpdated.Broadcast();
}

void AInventoryManager::UpdateRecipeBroadCast()
{
    OnRecipeUpdated.Broadcast();
}
