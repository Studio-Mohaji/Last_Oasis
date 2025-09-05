// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGameHUD.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Components/ProgressBar.h"

void UInGameHUD::SetAbilitySystemComponent()
{
	ASC = Cast<IAbilitySystemInterface>(GetOwningPlayer()->GetPawn())->GetAbilitySystemComponent();
	ASC->GetGameplayAttributeValueChangeDelegate(ULOAttributeSet::GetHealthAttribute()).AddUObject(this, &UInGameHUD::OnHealthChanged);
	ASC->GetGameplayAttributeValueChangeDelegate(ULOAttributeSet::GetHungerAttribute()).AddUObject(this, &UInGameHUD::OnHungerChanged);
	ASC->GetGameplayAttributeValueChangeDelegate(ULOAttributeSet::GetThirstAttribute()).AddUObject(this, &UInGameHUD::OnThirstChanged);
	ASC->GetGameplayAttributeValueChangeDelegate(ULOAttributeSet::GetTemperatureAttribute()).AddUObject(this, &UInGameHUD::OnTemperatureChanged);

}

UAbilitySystemComponent* UInGameHUD::GetAbilitySystemComponent() const
{
	return ASC;
}

void UInGameHUD::OnHealthChanged(const FOnAttributeChangeData& ChangeData)
{
	Health->SetPercent(ChangeData.NewValue/100);
}

void UInGameHUD::OnHungerChanged(const FOnAttributeChangeData& ChangeData)
{
	Hunger->SetPercent(ChangeData.NewValue/100);
}

void UInGameHUD::OnThirstChanged(const FOnAttributeChangeData& ChangeData)
{
	Thirst->SetPercent(ChangeData.NewValue/100);
}

void UInGameHUD::OnTemperatureChanged(const FOnAttributeChangeData& ChangeData)
{
	Temperature->SetPercent(ChangeData.NewValue/100);
}
