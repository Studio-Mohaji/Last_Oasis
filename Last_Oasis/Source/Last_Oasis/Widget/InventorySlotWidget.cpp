// Fill out your copyright notice in the Description page of Project Settings.

#include "../Widget/InventorySlotWidget.h"
#include "../Data/DataAssetBase.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "../Widget/ItemInfoWidget.h"
#include "../Widget/InventoryWidget.h"

void UInventorySlotWidget::NativeConstruct()
{
	if (!ParentInventoryWidget->ItemInfoWidget)
		return;

	InfoWidget = ParentInventoryWidget->ItemInfoWidget;
}

FReply UInventorySlotWidget::NativeOnMouseMove(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{

	if (ItemImage->GetVisibility() == ESlateVisibility::Hidden)
		return FReply::Unhandled();

	if (!InfoWidget)
	{
		if (!ParentInventoryWidget || !ParentInventoryWidget->ItemInfoWidget)
			return FReply::Unhandled();

		InfoWidget = ParentInventoryWidget->ItemInfoWidget;
	}
	
	if (InfoWidget->GetVisibility() != ESlateVisibility::Visible)
		InfoWidget->SetVisibility(ESlateVisibility::Visible);



	FVector2D MousePos = InMouseEvent.GetScreenSpacePosition();
	MousePos.Y -= 170.0f; 
	MousePos.X -= 310.0f; 
	InfoWidget->SetPositionInViewport(MousePos, true);
	
	// 아이템 데이터 설정 (nullptr 체크)
	if (ItemData && InfoWidget)
	{
		UE_LOG(LogTemp, Warning, TEXT("Set Item Data xxx"));
		InfoWidget->SetItemData(ItemData);
	}


	return Super::NativeOnMouseMove(InGeometry, InMouseEvent); //45
}

void UInventorySlotWidget::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	if (InfoWidget && InfoWidget->IsInViewport())
		InfoWidget->SetVisibility(ESlateVisibility::Hidden);
}

FReply UInventorySlotWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	UE_LOG(LogTemp, Warning, TEXT("Slot Clicked?"));

	if (InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton &&
		ItemData->IsUsable)
	{
		UE_LOG(LogTemp, Warning, TEXT("Slot Clicked!"));
		OnSlotClicked.Broadcast(this);
		SetSlotData();
		return FReply::Handled();
	}


	return Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
}

void UInventorySlotWidget::SetSlotData()
{

	if (!ItemData || CurrentCount <= 0)
	{
		ItemImage->SetVisibility(ESlateVisibility::Hidden);
		ItemCount->SetVisibility(ESlateVisibility::Hidden);
		return;
	}

	// ���� ���� ����
	if (CurrentCount > ItemData->MaxStackCount)
		CurrentCount = ItemData->MaxStackCount;

	// UI ������Ʈ
	ItemImage->SetBrushFromTexture(ItemData->Icon);
	ItemImage->SetVisibility(ESlateVisibility::Visible);

	if (ItemData->IsStackable)
	{
		ItemCount->SetText(FText::AsNumber(CurrentCount));
		ItemCount->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		ItemCount->SetText(FText::AsNumber(1));
		ItemCount->SetVisibility(ESlateVisibility::Hidden);
	}

}

void UInventorySlotWidget::SetOptionVisible()
{
	//if (CurrentCount == 0 || !ItemData)
	if (CurrentCount == 0)
	{
		ItemImage->SetVisibility(ESlateVisibility::Hidden);
		ItemCount->SetVisibility(ESlateVisibility::Hidden);
		return;
	}
	else
	{
		ItemImage->SetVisibility(ESlateVisibility::Visible);
		ItemCount->SetVisibility(ESlateVisibility::Visible);
	}
}
