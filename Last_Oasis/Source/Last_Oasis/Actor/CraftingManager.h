// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Data/RecipeState.h"
#include "CraftingManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCraftingEvent, int32, SlotIndex);

class UDataAssetBase;

UCLASS()
class LAST_OASIS_API ACraftingManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACraftingManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crafting")
	TArray<FRecipeState> RecipeStates;

	UPROPERTY(BlueprintAssignable, Category = "Event")
	FOnCraftingEvent OnCraftingEvent;

	UFUNCTION(BlueprintCallable, Category = "Crafting")
	void StoryItemCraftingEvent(int32 index);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crafting")
	UDataAssetBase* WeapeonCraftingItem;
};
S