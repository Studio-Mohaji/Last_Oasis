// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Last_OasisGameMode.generated.h"

UCLASS(minimalapi)
class ALast_OasisGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ALast_OasisGameMode();
	
	UFUNCTION(BlueprintCallable, Category="Spawn")
	void SpawnBuilding(const FVector& Center,float L);
	
	virtual void BeginPlay() override;
	UPROPERTY(EditDefaultsOnly, Category = "Spawn")
	TSubclassOf<AActor> ClassA;

	UPROPERTY(EditDefaultsOnly, Category = "Spawn")
	TSubclassOf<AActor> ClassB;

	UPROPERTY(EditDefaultsOnly, Category = "Spawn")
	TSubclassOf<AActor> ClassC;

	UPROPERTY(EditDefaultsOnly, Category = "Spawn")
	FVector MapCenter;

	UPROPERTY(EditDefaultsOnly, Category = "Spawn")
	float MapSize;
};



