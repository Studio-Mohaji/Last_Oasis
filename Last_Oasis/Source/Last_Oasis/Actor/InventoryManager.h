// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Data/InventoryItemStruct.h"
#include "../Data/DataAssetBase.h"
#include "InventoryManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryUpdated);

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

	UPROPERTY(BlueprintAssignable, Category = "Inventory")
	FOnInventoryUpdated OnInventoryUpdated;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	TArray<FInventoryItem> ItemDataList;

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void UseItem(UDataAssetBase* ItemData);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void GetItem(UDataAssetBase* ItemData);


	// ===============Test=============
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void TestGetItem();

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void UpdateBroadCast();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	UDataAssetBase* TestItemData;

};
