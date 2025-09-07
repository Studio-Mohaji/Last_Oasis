// Fill out your copyright notice in the Description page of Project Settings.


#include "../Actor/InventoryManager.h"

#include "Actor/InteractiveActor.h"

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
	
}

// Called every frame
void AInventoryManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AInventoryManager::UseItem(UDataAssetBase* ItemData)
{
	if (!ItemData) return;
	
    for (int32 i = 0; i < ItemDataList.Num(); i++)
    {
        FInventoryItem& item = ItemDataList[i];
        if (item.ItemData == ItemData && ItemData->IsUsable)
        {
            if (item.CurrentCount > 0)
            {
                UE_LOG(LogTemp, Warning, TEXT("Use Item"));

                // TODO: ������ ��� ȿ��

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
        if (RandomRoll > DropData.DropChance) // ȹ�� ����
            continue; 

        // ��� ����
        int32 DropCount = FMath::RandRange(DropData.DropMinRange, DropData.DropMaxRange);

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

 //   InteractiveActor.DropItems[0].DropItemData; // ��� ������ ����
	//InteractiveActor.DropItems[0].DropChance; // ��� Ȯ�� float Ȯ�� Chance/100
 //   InteractiveActor.DropItems[0].DropMaxRange; // �ִ� ��� ����
 //   InteractiveActor.DropItems[0].DropMinRange; // �ּ� ��� ����
 //   

 //   UDataAssetBase* ItemData = InteractiveActor.DropItems[0].DropItemData;

 //   if (!ItemData) return;

 //   bool bItemFound = false;

 //   for (int32 i = 0; i < ItemDataList.Num(); i++)
 //   {
 //       FInventoryItem& item = ItemDataList[i];

 //       if (item.ItemData == ItemData)
 //       {
 //           bItemFound = true;

 //           if (item.ItemData->IsStackable)
 //           {
 //               if (item.CurrentCount <= item.ItemData->MaxStackCount)
 //               {
 //                   item.CurrentCount++;
 //                   UE_LOG(LogTemp, Warning, TEXT("get Item"));
 //                   UpdateBroadCast();
 //               }
 //           }
 //           else
 //           {
 //               UE_LOG(LogTemp, Warning, TEXT("You can't have duplicated item."))
 //           }
 //           return; // �̹� ó�������� �Լ� ����

 //       }
 //   }

 //   if (!bItemFound)
 //   {
 //       FInventoryItem NewItem;
 //       NewItem.ItemData = ItemData;
 //       NewItem.CurrentCount = 1;
 //       ItemDataList.Add(NewItem);
 //      
 //       UE_LOG(LogTemp, Warning, TEXT("New item added to inventory: %s"), *ItemData->ItemName.ToString());

 //       UpdateBroadCast();
 //   }
}

void AInventoryManager::TestGetItem()
{
    for (int32 i = 0; i < ItemDataList.Num(); i++)
    {
        FInventoryItem& item = ItemDataList[i];
        if (item.ItemData == TestItemData)
        {
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


}

void AInventoryManager::UpdateBroadCast()
{
    OnInventoryUpdated.Broadcast();
}
