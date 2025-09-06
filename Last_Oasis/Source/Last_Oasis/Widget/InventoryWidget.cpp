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
            // ���� ���� ����
            UInventorySlotWidget* NewSlot = CreateWidget<UInventorySlotWidget>(GetWorld(), ItemSlotWidgetClass);
            if (!NewSlot) continue;

            // �θ� ���� ����
            NewSlot->ParentInventoryWidget = this;

            // GridPanel�� �߰�
            UGridSlot* GridSlot = GridBox->AddChildToGrid(NewSlot);
            if (GridSlot)
            {
                GridSlot->SetRow(Row);
                GridSlot->SetColumn(Col);
            }

            // �迭�� ����
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

    // ������ �з�
    for (int32 i = 0; i < ItemCount; ++i)
    {
        if (!TestItemDataList[i].ItemData) continue;

        if (TestItemDataList[i].ItemData->IsUsable)
            UsableItems.Add(TestItemDataList[i]);
        else
            NonUsableItems.Add(TestItemDataList[i]);
    }

    // ���ĵ� �迭 ����
    TArray<FInventoryItem> SortedItems;
    SortedItems.Append(UsableItems);
    SortedItems.Append(NonUsableItems);

    // ���Կ� ����
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
