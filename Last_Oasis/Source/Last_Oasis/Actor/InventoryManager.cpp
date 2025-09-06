// Fill out your copyright notice in the Description page of Project Settings.


#include "../Actor/InventoryManager.h"

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


void AInventoryManager::GetItem(UDataAssetBase* ItemData)
{
    if (!ItemData) return;

    bool bItemFound = false;

    for (int32 i = 0; i < ItemDataList.Num(); i++)
    {
        FInventoryItem& item = ItemDataList[i];

        if (item.ItemData == ItemData)
        {
            bItemFound = true;

            if (item.ItemData->IsStackable)
            {
                if (item.CurrentCount <= item.ItemData->MaxStackCount)
                {
                    item.CurrentCount++;
                    UE_LOG(LogTemp, Warning, TEXT("get Item"));
                    UpdateBroadCast();
                }
            }
            else
            {
                UE_LOG(LogTemp, Warning, TEXT("You can't have duplicated item."))
            }
            return; // 이미 처리했으면 함수 종료

        }
    }

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


}

void AInventoryManager::UpdateBroadCast()
{
    OnInventoryUpdated.Broadcast();
}
