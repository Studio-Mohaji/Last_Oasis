// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "LOGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class LAST_OASIS_API ALOGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	ALOGameModeBase();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="DayNight")
	float DayLength = 1200.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="DayNight")
	float DayDuration = 720.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="DayNight")
	float NightDuration = 480.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="DayNight")
	float ElapsedTime = 0.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="DayNight")
	float CurrentHour = 6.0f;

	// UFUNCTION(BlueprintCallable, Category="DayNight")
	// bool IsDaytime() const;
	//
	// UFUNCTION(BlueprintCallable, Category="DayNight")
	// FString GetTimeString() const;
	
protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;
	UFUNCTION(BlueprintCallable)
	void SpawnBuilding();

	UFUNCTION()
	void UpdateGameTime();

private:
	UPROPERTY()
	TObjectPtr<class ADirectionalLight> Sun;
	UPROPERTY(EditAnywhere, Category="Map Info", meta = (AllowPrivateAccess = true))
	FVector Center;
	UPROPERTY(EditAnywhere, Category="Map Info", meta = (AllowPrivateAccess = true))
	float Length;
	
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	TSubclassOf<AActor> BuildingA;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	TSubclassOf<AActor> BuildingB;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	TSubclassOf<AActor> BuildingC;
	int32 LastPrintedMinute = -1;

	FTimerHandle TimeHandle;
};
