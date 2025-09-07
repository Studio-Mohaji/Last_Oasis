// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Data/InventoryItemStruct.h"
#include "../Data/DataAssetBase.h"
#include "InventoryManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryUpdated);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnRecipeUpdated);

class AInteractiveActor;
class ACraftingManager;

USTRUCT(BlueprintType, Blueprintable)
struct FRecipeUnlockedStruct
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	UDataAssetBase* BlueprintItemData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	UDataAssetBase* ItemData;

};

UCLASS()
class LAST_OASIS_API AInventoryManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInventoryManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crafting")
	ACraftingManager* CraftingManager;

	UPROPERTY(BlueprintAssignable, Category = "Inventory")
	FOnInventoryUpdated OnInventoryUpdated;

	UPROPERTY(BlueprintAssignable, Category = "Inventory")
	FOnRecipeUpdated OnRecipeUpdated;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	TArray<FInventoryItem> ItemDataList;

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void UseItem(UDataAssetBase* ItemData);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void GetItem(AInteractiveActor* InteractiveActor);

	void CheckRecipe(UDataAssetBase* ItemData);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void UpdateBroadCast();

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void UpdateRecipeBroadCast();

	// ===============Test=============
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void TestGetItem();


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	UDataAssetBase* TestItemData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")	
	TArray<FRecipeUnlockedStruct> RecipeItems;

};
