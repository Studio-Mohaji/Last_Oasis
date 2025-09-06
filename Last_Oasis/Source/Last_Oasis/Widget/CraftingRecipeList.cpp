// Fill out your copyright notice in the Description page of Project Settings.


#include "../Widget/CraftingRecipeList.h"
#include "../Widget/CraftingWidget.h"

void UCraftingRecipeList::NativeConstruct()
{
	if (BackgroundBorder)
	{
		BackgroundBorder->OnMouseButtonDownEvent.BindUFunction(this, "OnClicked");
	}
}

void UCraftingRecipeList::OnClicked()
{
    // Åä±Û
    bIsSelected = !bIsSelected;

    SetSelected(bIsSelected);

    if (ParentCraftingWidget)
    {
        ParentCraftingWidget->UpdateSelection(this);
    }
}

void UCraftingRecipeList::SetSelected(bool bSelected)
{
    if (!BackgroundBorder) return;

    BackgroundBorder->SetBrushColor(bSelected ? FLinearColor::Blue : FLinearColor::Black);

}

void UCraftingRecipeList::SetRecipeData()
{
	CraftingItemName->SetText(FText::FromName(ItemData->ItemName));
	CraftingItemImage->SetBrushFromTexture(ItemData->Icon);
}
