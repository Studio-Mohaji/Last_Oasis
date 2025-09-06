// Fill out your copyright notice in the Description page of Project Settings.


#include "../Data/DataAssetBase.h"
#include "../Data/ItemListDataAsset.h"
#include "../Widget/ItemInfoWidget.h"
#include "../Widget/InventorySlotWidget.h"
#include "../Widget/InventoryWidget.h"


void UInventoryWidget::NativeConstruct()
{
    Super::NativeConstruct();
	UE_LOG(LogTemp, Warning, TEXT("InventoryWidget Constructed"));
    InitializeSlots();
}

void UInventoryWidget::InitializeSlots()
{
    if (!GridBox || !ItemSlotWidgetClass) return;

    const int32 Rows = 5;
    const int32 Columns = 4;

    InventorySlots.Empty();

    for (int32 Row = 0; Row < Rows; ++Row)
    {
        for (int32 Col = 0; Col < Columns; ++Col) 
        {
            // 슬롯 위젯 생성
            UInventorySlotWidget* NewSlot = CreateWidget<UInventorySlotWidget>(GetWorld(), ItemSlotWidgetClass);
            if (!NewSlot) continue;

            // 부모 위젯 세팅
            NewSlot->ParentInventoryWidget = this;

            // GridPanel에 추가
            UGridSlot* GridSlot = GridBox->AddChildToGrid(NewSlot);
            if (GridSlot)
            {
                GridSlot->SetRow(Row);
                GridSlot->SetColumn(Col);
            }

            // 배열에 저장
            InventorySlots.Add(NewSlot);

            NewSlot->ItemImage->SetVisibility(ESlateVisibility::Hidden);
            NewSlot->ItemCount->SetVisibility(ESlateVisibility::Hidden);
        }
    }
}


void UInventoryWidget::UpdateSlot()
{
    const int32 SlotCount = InventorySlots.Num();
    const int32 ItemCount = TestItemDataList.Num();

    TArray<FInventoryItem> UsableItems;
    TArray<FInventoryItem> NonUsableItems;

    // 아이템 분류
    for (int32 i = 0; i < ItemCount; ++i)
    {
        if (!TestItemDataList[i].ItemData) continue;

        if (TestItemDataList[i].ItemData->IsUsable)
            UsableItems.Add(TestItemDataList[i]);
        else
            NonUsableItems.Add(TestItemDataList[i]);
    }

    // 정렬된 배열 생성
    TArray<FInventoryItem> SortedItems;
    SortedItems.Append(UsableItems);
    SortedItems.Append(NonUsableItems);

    // 슬롯에 세팅
    for (int32 i = 0; i < SlotCount; ++i)
    {
        UInventorySlotWidget* InventorySlot = InventorySlots[i];
        if (!InventorySlot) continue;

        if (i < SortedItems.Num() && SortedItems[i].ItemData)
        {
            InventorySlot->ItemData = SortedItems[i].ItemData;
            InventorySlot->CurrentCount = SortedItems[i].CurrentCount;
        }
        else
        {
            InventorySlot->ItemData = nullptr;
            InventorySlot->CurrentCount = 0;
        }

        InventorySlot->SetSlotData();
    }


}
