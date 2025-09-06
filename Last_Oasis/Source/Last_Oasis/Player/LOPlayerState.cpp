// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/LOPlayerState.h"
#include "AbilitySystemComponent.h"
#include "GamePlayAbility/LOAbilitySystemComponent.h"
#include "GamePlayAbility/AttributeSet/LOAttributeSet.h"

ALOPlayerState::ALOPlayerState()
{
	AttributeSet = CreateDefaultSubobject<ULOAttributeSet>(TEXT("AttributeSet"));
	ASC = CreateDefaultSubobject<ULOAbilitySystemComponent>(TEXT("ASC"));
	ASC->AddAttributeSetSubobject<ULOAttributeSet>(AttributeSet);
	ASC -> SetIsReplicated(true);
}

class UAbilitySystemComponent* ALOPlayerState::GetAbilitySystemComponent() const
{
	return ASC;
}
