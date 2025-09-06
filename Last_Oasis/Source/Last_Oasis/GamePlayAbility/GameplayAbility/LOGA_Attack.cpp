// Fill out your copyright notice in the Description page of Project Settings.


#include "GamePlayAbility/GameplayAbility/LOGA_Attack.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Character/PlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void ULOGA_Attack::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                   const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	APlayerCharacter *Character = CastChecked<APlayerCharacter>(ActorInfo->AvatarActor.Get());
	Character->GetCharacterMovement()->SetMovementMode(MOVE_None);
	int32 RandomIndex = FMath::RandRange(0, 4);
	UAbilityTask_PlayMontageAndWait* PlayAttackTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, TEXT("PlayAttack"), Character->GetAttackMontage(), 1.0f, FName(*FString::FromInt(RandomIndex)));
	PlayAttackTask->OnCompleted.AddDynamic(this,&ULOGA_Attack::OnCompleteCallback);
	PlayAttackTask->OnInterrupted.AddDynamic(this, &ULOGA_Attack::OnInterruptedCallback);
	PlayAttackTask->ReadyForActivation();
}

void ULOGA_Attack::CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility)
{
	Super::CancelAbility(Handle, ActorInfo, ActivationInfo, bReplicateCancelAbility);
}

void ULOGA_Attack::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
	APlayerCharacter *Character = CastChecked<APlayerCharacter>(ActorInfo->AvatarActor.Get());
	Character->GetCharacterMovement()->SetMovementMode(MOVE_Walking);

}

void ULOGA_Attack::InputPressed(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo)
{
	Super::InputPressed(Handle, ActorInfo, ActivationInfo);
}

void ULOGA_Attack::OnCompleteCallback()
{
	bool bReplicatedEndAblity = true;
	bool bWasCancelled = false;

	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bReplicatedEndAblity, bWasCancelled);
}

void ULOGA_Attack::OnInterruptedCallback()
{
	bool bReplicatedEndAblity = true;
	bool bWasCancelled = true;
	UE_LOG(LogTemp, Log, TEXT("Inturrepted"));

	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bReplicatedEndAblity, bWasCancelled);
}
