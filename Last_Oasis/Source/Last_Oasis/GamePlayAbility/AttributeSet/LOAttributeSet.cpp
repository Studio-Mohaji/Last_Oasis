// Fill out your copyright notice in the Description page of Project Settings.


#include "GamePlayAbility/AttributeSet/LOAttributeSet.h"
#include "GameplayEffectExtension.h"

ULOAttributeSet::ULOAttributeSet() :
	MaxHealth(100.f),
	Health(100.f),
	MaxHunger(100.f),
	Hunger(100.f),
	MaxThirst(100.f),
	Thirst(100.f),
	MaxTemperature(100.f),
	MinTemperature(0.f),
	Temperature(36.5f),
	Level(1)
{
	
}

void ULOAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	UAbilitySystemComponent* ASC = GetOwningAbilitySystemComponent();
	if (!ASC) return;
	if (Attribute == GetThirstAttribute() && (GetThirst() - NewValue) > 0 &&
	ASC->HasMatchingGameplayTag(FGameplayTag::RequestGameplayTag(FName("Game.Day"))) &&
	ASC->HasMatchingGameplayTag(FGameplayTag::RequestGameplayTag(FName("State.InShadow"))))
	{
		float Delta = GetThirst() - NewValue;
		NewValue = GetThirst() - Delta * 0.75f;
		UE_LOG(LogTemp,Log,TEXT("ASDASDD"));
	}

	if (Attribute == GetTemperatureAttribute() &&  (GetTemperature() - NewValue) < 0 && ASC->HasMatchingGameplayTag(FGameplayTag::RequestGameplayTag(FName("Game.Day")))
	&& ASC->HasMatchingGameplayTag(FGameplayTag::RequestGameplayTag(FName("State.InShadow"))))
	{
		NewValue -= 0.005;
	}
}

