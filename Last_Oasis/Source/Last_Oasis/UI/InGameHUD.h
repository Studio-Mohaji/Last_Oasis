// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "Blueprint/UserWidget.h"
#include "GamePlayAbility/AttributeSet/LOAttributeSet.h"
#include "InGameHUD.generated.h"

/**
 * 
 */
UCLASS()
class LAST_OASIS_API UInGameHUD : public UUserWidget, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	void SetAbilitySystemComponent();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

protected:
	void OnHealthChanged(const FOnAttributeChangeData& ChangeData);
	void OnHungerChanged(const FOnAttributeChangeData& ChangeData);
	void OnThirstChanged(const FOnAttributeChangeData& ChangeData);
	void OnTemperatureChanged(const FOnAttributeChangeData& ChangeData);
	
protected:
	UPROPERTY(EditAnywhere, Category = GAS)
	TObjectPtr<class UAbilitySystemComponent> ASC;

	UPROPERTY(EditAnywhere,Meta=(AllowPrivateAccess = true, BindWidget))
	TObjectPtr<class UProgressBar> Health;
	UPROPERTY(EditAnywhere,Meta=(AllowPrivateAccess = true, BindWidget))
	TObjectPtr<class UProgressBar> Hunger;
	UPROPERTY(EditAnywhere,Meta=(AllowPrivateAccess = true, BindWidget))
	TObjectPtr<class UProgressBar> Thirst;
	UPROPERTY(EditAnywhere,Meta=(AllowPrivateAccess = true, BindWidget))
	TObjectPtr<class UProgressBar> Temperature;
};
