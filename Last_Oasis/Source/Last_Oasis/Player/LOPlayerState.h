// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "LOPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class LAST_OASIS_API ALOPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()
public:
	ALOPlayerState();
	
	virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override;

protected:
	UPROPERTY(EditAnywhere, Category = GAS)
	TObjectPtr<class UAbilitySystemComponent> ASC;
	UPROPERTY(EditAnywhere, Category = GAS)
	TObjectPtr<class ULOAttributeSet> AttributeSet;
};
