// Fill out your copyright notice in the Description page of Project Settings.


#include "../Actor/InventoryManager.h"
#include "../Actor/CraftingManager.h"

#include "Actor/InteractiveActor.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AInventoryManager::AInventoryManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AInventoryManager::BeginPlay()
{
	Super::BeginPlay();

    CraftingManager = Cast<ACraftingManager>(
        UGameplayStatics::GetActorOfClass(GetWorld(), ACraftingManager::StaticClass()));
}

// Called every frame
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

                // TODO: 아이템 사용 효과

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

    for (const FDropItemData& DropData : InteractiveActor->DropItems)
    {
        if (!DropData.DropItemData) continue;

        int32 RandomRoll = FMath::RandRange(1, 100);
        if (RandomRoll > DropData.DropChance) // 획득 실패
            continue; 

        // 드랍 개수
        int32 DropCount = FMath::RandRange(DropData.DropMinRange, DropData.DropMaxRange);

        // 아이템 획득
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

            // 기존 인벤토리에 없는 아이템이라면 새로 추가
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

                    // 아이템 획득 효과
                    
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

    // 기존 인벤토리에 없는 아이템이라면 새로 추가
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
   // // 사용한 소모품 데이터 ItemData
   // for (int i = 0; i < RecipeItems.Num(); i++)
   // {
   //     // RecipeItems(레시피 데이터) 인지 체크하기
   //     if (ItemData == RecipeItems[i].BlueprintItemData)
   //     {
   //         // 해당 RecipeItems[i].BlueprintItemData에 해당하는 RecipeItems[i].ItemData 획득
   //          
			//// RecipeItems[i].ItemData과 RecipeState의 RecipeItem 비교
   //         
			//// 같은거 찾으면, RecipeState의 bUnlocked true로 바꾸기

			//// CraftingWidget에서 레시피 UI 업데이트
   //         UpdateRecipeBroadCast();

   //         // 사용한 레시피는 제거
   //         RecipeItems.RemoveAt(i);
   //         // 같은게 없으면 넘기기.
   //        
   //         
			//// 그럼 레시피 데이터에 따라서 CraftingManager->RecipeStates의 특정 Recipe의 bUnlocked true로 바꾸기
 
			//CraftingManager->RecipeStates[i].RecipeItem == RecipeItems[i].ItemData;
			//	CraftingManager->RecipeStates[i].bUnlocked = true;




   //         UpdateRecipeBroadCast();
   //         RecipeItems.RemoveAt(i);
   //         return;
   //     }
   // }


    for (int32 i = RecipeItems.Num() - 1; i >= 0; --i) // 뒤에서 앞으로 반복하면 RemoveAt 안전
    {
        FRecipeUnlockedStruct& Recipe = RecipeItems[i];

        // 사용한 아이템이 해당 레시피의 조건 아이템인지 체크
        if (ItemData == Recipe.BlueprintItemData)
        {
            //  레시피 데이터와 RecipeState 연결
            for (FRecipeState& RecipeState : CraftingManager->RecipeStates)
            {
                if (RecipeState.RecipeItem == Recipe.ItemData)
                {
                    RecipeState.bUnlocked = true; // 해금
                    break;
                }
            }

            // CraftingWidget에 UI 업데이트 요청
            UpdateRecipeBroadCast();

            // 사용한 레시피 제거
            RecipeItems.RemoveAt(i);
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
