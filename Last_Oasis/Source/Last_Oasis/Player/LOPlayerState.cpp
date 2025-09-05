// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/LOPlayerState.h"
#include "AbilitySystemComponent.h"
#include "GamePlayAbility/AttributeSet/LOAttributeSet.h"

ALOPlayerState::ALOPlayerState()
{
	ASC = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("ASC"));
	ASC -> SetIsReplicated(true);
	AttributeSet = CreateDefaultSubobject<ULOAttributeSet>(TEXT("AttributeSet"));
}

class UAbilitySystemComponent* ALOPlayerState::GetAbilitySystemComponent() const
{
	return ASC;
}
