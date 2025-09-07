// Fill out your copyright notice in the Description page of Project Settings.


#include "../Widget/CraftingWidget.h"
#include "../Widget/CraftingItemList.h"
#include "../Widget/CraftingRecipeList.h"
#include "Kismet/GameplayStatics.h"
#include "Data/DataAssetBase.h"


void UCraftingWidget::NativeConstruct()
{
	Super::NativeConstruct();

    if (!GetWorld() || !GetWorld()->IsGameWorld())
        return;
	CraftingManager = Cast<ACraftingManager>(
		UGameplayStatics::GetActorOfClass(GetWorld(), ACraftingManager::StaticClass()));

    InventoryManager = Cast<AInventoryManager>(
        UGameplayStatics::GetActorOfClass(GetWorld(), AInventoryManager::StaticClass()));

	CraftingUIBox->SetVisibility(ESlateVisibility::Hidden);

    if (InventoryManager)
    {
        InventoryManager->OnRecipeUpdated.AddDynamic(this, &UCraftingWidget::CraftingRecipeUpdate);
    }

	CraftingRecipeInitialize();

}

void UCraftingWidget::CraftingRecipeInitialize()
{
    if (!IsValid(CraftingManager))
    {
        FTimerHandle RetryHandle;
        GetWorld()->GetTimerManager().SetTimer(
            RetryHandle, this, &UCraftingWidget::CraftingRecipeInitialize, 
            0.05f, false
        );

        return;
    }

    CraftingRecipeList->ClearChildren(); 
    RecipeListArray.Empty();

    const int32 RecipeCount = CraftingManager->RecipeStates.Num();

    // �ر�
    for (int32 i = 0; i < RecipeCount; ++i) //41
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
                NewRecipeWidget->ParentCraftingWidget = this;
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
}

// �Ѱ� �������� ������Ʈ
void UCraftingWidget::CraftingRecipeUpdate()
{
    if (!CraftingManager) return;

    TArray<UUserWidget*> UnlockedWidgets;
    TArray<UUserWidget*> LockedWidgets;

    // ���� ���� �з�
    for (int32 i = 0; i < RecipeListArray.Num(); ++i)
    {
        UCraftingRecipeList* Widget = RecipeListArray[i];
        if (!Widget) continue;

        const FRecipeState& RecipeState = CraftingManager->RecipeStates[i];

        // ������ ����
        Widget->ItemData = RecipeState.RecipeItem;
        Widget->SetRecipeData();

        // Visible ó��
        if (RecipeState.bUnlocked)
        {
            Widget->SetVisibility(ESlateVisibility::Visible);
            UnlockedWidgets.Add(Widget);
        }
        else
        {
            Widget->SetVisibility(ESlateVisibility::Hidden);
            LockedWidgets.Add(Widget);
        }
    }

    // UI ���� ���ġ
    CraftingRecipeList->ClearChildren();

    for (UUserWidget* Widget : UnlockedWidgets)
    {
        CraftingRecipeList->AddChild(Widget);
    }

    for (UUserWidget* Widget : LockedWidgets)
    {
        CraftingRecipeList->AddChild(Widget);
    }

    //CraftingRecipeInitialize();
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
    if (!bFound)
    {
        InventoryManager->ItemDataList.Add(FInventoryItem{ SelectedRecipeState.RecipeItem, 1 });
    }

    // �κ��丮 ������Ʈ
    InventoryManager->UpdateBroadCast();


    for (int i = 0; i < InventoryManager->RecipeItems.Num(); i++)
    {// InventoryManage�� ������ �����ۿ� �ش��ϴ� �������� ������ => �߿� ���� ������
        if (InventoryManager->RecipeItems[i].ItemData == SelectedRecipeState.RecipeItem)
        {
			// TImer�� ���� �ڿ� �˸�UI & ����â �ݱ� �Լ� ����.
            FTimerHandle CloseHandle;
            GetWorld()->GetTimerManager().SetTimer(
                CloseHandle, 
                FTimerDelegate::CreateUObject(this, &UCraftingWidget::CloseCraftingUI, i), 
                1.0f, false
            );
            break;
        }
    }

    if (SelectedRecipeState.RecipeItem == CraftingManager->WeapeonCraftingItem)
    {
		CraftingManager->WeaponCrafting();
    }

	// ����â ������Ʈ
    CraftingItemUpdate();
}

void UCraftingWidget::CloseCraftingUI(int32 index)
{
    CraftingManager->StoryItemCraftingEvent(index);

    //�����
    if (GetVisibility() == ESlateVisibility::Visible)
    {
        SetVisibility(ESlateVisibility::Hidden);
    }
}