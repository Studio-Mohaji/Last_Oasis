// Fill out your copyright notice in the Description page of Project Settings.


#include "GamePlayAbility/AttributeSet/LOAttributeSet.h"
#include "GameplayEffectExtension.h"

ULOAttributeSet::ULOAttributeSet() :
	MaxHealth(100.f),
	Health(100.f),
	MaxHunger(100.f),
	Hunger(90.f),
	MaxThirst(100.f),
	Thirst(90.f),
	MaxTemperature(100.f),
	MinTemperature(0.f),
	Temperature(36.5f),
	Level(1),
	Damage(20)
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
	}
}

