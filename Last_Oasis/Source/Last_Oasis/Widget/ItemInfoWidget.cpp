// Fill out your copyright notice in the Description page of Project Settings.

#include "../Data/DataAssetBase.h"
#include "../Widget/ItemInfoWidget.h"

void UItemInfoWidget::SetItemData(UDataAssetBase* ItemData) const
{
	if (!ItemData) return; // null이면 바로 종료

	//ItemIcon->SetBrushFromTexture(ItemData->Icon);
	ItemName->SetText(FText::FromName(ItemData->ItemName));  //11
	ItemDescription->SetText(ItemData->Description);

	if(ItemData->IsUsable)
		ItemType->SetText(FText::FromString("Usable Item"));
	else
		ItemType->SetText(FText::FromString("Craft Item"));
}
