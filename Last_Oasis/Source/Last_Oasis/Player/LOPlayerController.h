// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "LOPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class LAST_OASIS_API ALOPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	void InitHUD();
	
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UInGameHUD> HUDWidgetClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class UInGameHUD> HUD;
};
