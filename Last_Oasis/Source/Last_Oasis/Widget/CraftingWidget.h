// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/VerticalBox.h"
#include "../Actor/CraftingManager.h"
#include "CraftingWidget.generated.h"


class UCraftingItemList;
class UCraftingRecipeList;
/**
 * 
 */
UCLASS()
class LAST_OASIS_API UCraftingWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	class UButton* CraftingButton;

	UPROPERTY(meta = (BindWidget))
	class UVerticalBox* CraftingRecipeList;

	UPROPERTY(meta = (BindWidget))
	class UVerticalBox* CraftingItemList;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	TSubclassOf<UCraftingRecipeList> CraftRecipeClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	TSubclassOf<UCraftingItemList> CraftingItemClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crafting")
	ACraftingManager* CraftingManager;


	UPROPERTY()
	TArray<UCraftingRecipeList*> RecipeListArray;

	UFUNCTION(BlueprintCallable, Category = "Crafting")
	void CraftingRecipeInitialize();

	UFUNCTION(BlueprintCallable, Category = "Crafting")
	void UpdateSelection(UCraftingRecipeList* SelectedRecipe);

	UFUNCTION(BlueprintCallable, Category = "Crafting")
	void Crafting();
};
