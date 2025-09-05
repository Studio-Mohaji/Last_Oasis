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





void UInventoryWidget::SlotUpdate()
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

            int32 Index = Row * Columns + Col;
            UE_LOG(LogTemp, Warning, TEXT("Index: %d"), Index);
            if (!InventoryActor || InventoryActor->itemList.Num() == 0 || !InventoryActor->itemList.IsValidIndex(Index))
            {
                UE_LOG(LogTemp, Warning, TEXT("can't setting"));
                //NewSlot->ItemData = nullptr;
                //NewSlot->CurrentCount = 0;
                NewSlot->SetOptionVisible();
            }
            else
            {

                UE_LOG(LogTemp, Warning, TEXT("setting"));
                NewSlot->ItemData = InventoryActor->itemList[Index];
                NewSlot->CurrentCount = 1;
                NewSlot->SetSlotData();
            }


            NewSlot->ItemImage->SetVisibility(ESlateVisibility::Hidden);
            NewSlot->ItemCount->SetVisibility(ESlateVisibility::Hidden);

            // NewSlot->ItemData = InventoryItems->itemList[Index]; // 49
            //// NewSlot->SetOptionVisible();
            // NewSlot->SetSlotData();
        }
    }
}
