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

    // �ر�
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

    // ���ر�
    for (int32 i = 0; i < RecipeCount; ++i)
    {
        if (!CraftingManager->RecipeStates[i].bUnlocked) // bUnlocked : false
        {
            UCraftingRecipeList* NewRecipeWidget = CreateWidget<UCraftingRecipeList>(GetWorld(), CraftRecipeClass);
            if (NewRecipeWidget)
            {
                // ������ ����
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
            // �ٸ� ������ ���� ����
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
            SelectedRecipeState = Recipe; // ���õ� ������ ��ü ����
            break;
        }
    }

    if (CraftingUIBox->GetVisibility() != ESlateVisibility::Visible)
        CraftingUIBox->SetVisibility(ESlateVisibility::Visible);

    // ���õ� Recipe�� ItemList ������Ʈ
    CraftingItemUpdate();

    CraftingItemName->SetText(FText::FromName(SelectedRecipe->ItemData->ItemName));
}

// �Ѱ� �������� ������Ʈ
void UCraftingWidget::CraftingRecipeUpdate()
{

	// ������ ������Ʈ�Ҷ�, ItemList�� ������Ʈ
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

    // 1. ������ ��� ����
    for (const FRecipeResource& Resource : SelectedRecipeState.RequiredResources)
    {
        for (FInventoryItem& InventoryItem : InventoryManager->ItemDataList)
        {
            if (InventoryItem.ItemData == Resource.Resource)
            {
                InventoryItem.CurrentCount -= Resource.NeedCount;
                break; // �� �� ���� �� ���� ���
            }
        }
    }

    // 2. ���� ������ �κ��丮�� �߰�
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

    // �κ��丮�� ������ ���� �߰�
    if (!bFound)
    {
        InventoryManager->ItemDataList.Add(FInventoryItem{ SelectedRecipeState.RecipeItem, 1 });
    }




	//// ������ �������� ��� ������ŭ �κ��丮���� ����
 //   if(InventoryManager->ItemDataList[0].ItemData == SelectedRecipeState.RequiredResources[0].Resource)
 //       InventoryManager->ItemDataList[0].CurrentCount -= SelectedRecipeState.RequiredResources[0].NeedCount;

	//// ������ ������ �κ��丮�� �߰�

	//// �������� ���� ��� ���� �߰�
	//InventoryManager->ItemDataList.Add(FInventoryItem{ SelectedRecipeState.RecipeItem, 1 });
	//// ������ �������� ���� ��� �κ��丮�� FInventoryItem CurrentCount ����
	//InventoryManager->TestItemData[i].CurrentCount += 1;

    // �κ��丮 ������Ʈ
    InventoryManager->UpdateBroadCast();

	// ����â ������Ʈ
    CraftingItemUpdate();
}
