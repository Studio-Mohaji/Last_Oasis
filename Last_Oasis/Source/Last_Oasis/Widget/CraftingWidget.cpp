// Fill out your copyright notice in the Description page of Project Settings.


#include "../Widget/CraftingWidget.h"
#include "../Widget/CraftingItemList.h"
#include "../Widget/CraftingRecipeList.h"
#include "Kismet/GameplayStatics.h"

void UCraftingWidget::NativeConstruct()
{
	Super::NativeConstruct();

	CraftingManager = Cast<ACraftingManager>(
		UGameplayStatics::GetActorOfClass(GetWorld(), ACraftingManager::StaticClass())

	);
	CraftingRecipeInitialize();

}

void UCraftingWidget::CraftingRecipeInitialize()
{
    CraftingRecipeList->ClearChildren(); 
    RecipeListArray.Empty();

    const int32 RecipeCount = CraftingManager->RecipeStates.Num();

    // 해금
    for (int32 i = 0; i < RecipeCount; ++i)
    {
        if (CraftingManager->RecipeStates[i].bUnlocked) // bUnlocked : true
        {
            UCraftingRecipeList* NewRecipeWidget = CreateWidget<UCraftingRecipeList>(GetWorld(), CraftRecipeClass);
            if (NewRecipeWidget)
            {
                NewRecipeWidget->ParentCraftingWidget = this;
                NewRecipeWidget->ItemData = CraftingManager->RecipeStates[i].RecipeItem;
                NewRecipeWidget->SetRecipeData();

                CraftingRecipeList->AddChild(NewRecipeWidget);
                RecipeListArray.Add(NewRecipeWidget);
            }
        }
    }

    // 미해금
    for (int32 i = 0; i < RecipeCount; ++i)
    {
        if (!CraftingManager->RecipeStates[i].bUnlocked) // bUnlocked : false
        {
            UCraftingRecipeList* NewRecipeWidget = CreateWidget<UCraftingRecipeList>(GetWorld(), CraftRecipeClass);
            if (NewRecipeWidget)
            {
                // 데이터 전달
                CraftingRecipeList->AddChild(NewRecipeWidget);

                NewRecipeWidget->SetVisibility(ESlateVisibility::Hidden);
                RecipeListArray.Add(NewRecipeWidget);
            }
        }
    }

}

void UCraftingWidget::UpdateSelection(UCraftingRecipeList* SelectedRecipe)
{
    for (UCraftingRecipeList* Item : RecipeListArray)
    {
        if (Item != SelectedRecipe && Item->bIsSelected)
        {
            // 다른 아이템 선택 해제
            Item->SetSelected(false);
            Item->bIsSelected = false;
        }
    }
}

void UCraftingWidget::Crafting()
{
}
