// Fill out your copyright notice in the Description page of Project Settings.


#include "../Widget/CraftingWidget.h"
#include "../Widget/CraftingItemList.h"
#include "../Widget/CraftingRecipeList.h"
#include "Kismet/GameplayStatics.h"


void UCraftingWidget::NativeConstruct()
{
	Super::NativeConstruct();

	CraftingManager = Cast<ACraftingManager>(
		UGameplayStatics::GetActorOfClass(GetWorld(), ACraftingManager::StaticClass()));

    InventoryManager = Cast<AInventoryManager>(
        UGameplayStatics::GetActorOfClass(GetWorld(), AInventoryManager::StaticClass()));

	CraftingUIBox->SetVisibility(ESlateVisibility::Hidden);

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
	if (!SelectedRecipe) return;

    for (UCraftingRecipeList* Item : RecipeListArray)
    {
        if (Item != SelectedRecipe && Item->bIsSelected)
        {
            // 다른 아이템 선택 해제
            Item->SetSelected(false);
            Item->bIsSelected = false;
        }
    }

    bool bSameRecipee = (SelectedRecipeState.RecipeItem == SelectedRecipe->ItemData);

    SelectedRecipe->bIsSelected = true;
    SelectedRecipe->SetSelected(true);

    for (const FRecipeState& Recipe : CraftingManager->RecipeStates)
    {
        if (Recipe.RecipeItem == SelectedRecipe->ItemData)
        {
            SelectedRecipeState = Recipe; // 선택된 레시피 전체 저장
            break;
        }
    }

    if (CraftingUIBox->GetVisibility() != ESlateVisibility::Visible)
        CraftingUIBox->SetVisibility(ESlateVisibility::Visible);

    // 선택된 Recipe의 ItemList 업데이트
    CraftingItemUpdate();

    CraftingItemName->SetText(FText::FromName(SelectedRecipe->ItemData->ItemName));
}

// 켜고 끌때마다 업데이트
void UCraftingWidget::CraftingRecipeUpdate()
{

	// 레시피 업데이트할때, ItemList도 업데이트
    CraftingItemUpdate();
}

void UCraftingWidget::CraftingItemUpdate()
{
    CraftingItemList->ClearChildren();
    bool bAllSufficient = true;

    for (const FRecipeResource& Resource : SelectedRecipeState.RequiredResources)
    {
        UCraftingItemList* NewItemWidget = CreateWidget<UCraftingItemList>(GetWorld(), CraftingItemClass);
        NewItemWidget->ParentCraftingWidget = this;
        NewItemWidget->CraftingManager = CraftingManager;
        
        int32 ResourceCountInInventory = 0;
        for (const FInventoryItem& InventoryItem : InventoryManager->ItemDataList)
        {
            if (InventoryItem.ItemData == Resource.Resource) 
            {
                ResourceCountInInventory = InventoryItem.CurrentCount;
                break; 
            }
        }
		NewItemWidget->InventoryItemCount = ResourceCountInInventory;

        NewItemWidget->ResourceData = Resource;
        NewItemWidget->SetListData();

        if (!NewItemWidget->bIsSufficientResource)
        {
            bAllSufficient = false;
        }

        CraftingItemList->AddChild(NewItemWidget);
    }
    

    if (CraftingButton)
    {
        CraftingButton->SetIsEnabled(bAllSufficient);
    }
}

void UCraftingWidget::CraftingItem()
{

    // 1. 레시피 재료 차감
    for (const FRecipeResource& Resource : SelectedRecipeState.RequiredResources)
    {
        for (FInventoryItem& InventoryItem : InventoryManager->ItemDataList)
        {
            if (InventoryItem.ItemData == Resource.Resource)
            {
                InventoryItem.CurrentCount -= Resource.NeedCount;
                break; // 한 번 차감 후 다음 재료
            }
        }
    }

    // 2. 제작 아이템 인벤토리에 추가
    bool bFound = false;
    for (FInventoryItem& InventoryItem : InventoryManager->ItemDataList)
    {
        if (InventoryItem.ItemData == SelectedRecipeState.RecipeItem)
        {
            InventoryItem.CurrentCount += 1;
            bFound = true;
            break;
        }
    }

    // 인벤토리에 없으면 새로 추가
    if (!bFound)
    {
        InventoryManager->ItemDataList.Add(FInventoryItem{ SelectedRecipeState.RecipeItem, 1 });
    }




	//// 제작한 아이템의 재료 개수만큼 인벤토리에서 차감
 //   if(InventoryManager->ItemDataList[0].ItemData == SelectedRecipeState.RequiredResources[0].Resource)
 //       InventoryManager->ItemDataList[0].CurrentCount -= SelectedRecipeState.RequiredResources[0].NeedCount;

	//// 제작한 아이템 인벤토리에 추가

	//// 아이템이 없을 경우 새로 추가
	//InventoryManager->ItemDataList.Add(FInventoryItem{ SelectedRecipeState.RecipeItem, 1 });
	//// 기존에 아이템이 있을 경우 인벤토리의 FInventoryItem CurrentCount 증가
	//InventoryManager->TestItemData[i].CurrentCount += 1;

    // 인벤토리 업데이트
    InventoryManager->UpdateBroadCast();

	// 제작창 업데이트
    CraftingItemUpdate();
}
