// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "Player/LOPlayerController.h"

#include "../Widget/CraftingWidget.h"
#include "../Widget/InventoryWidget.h"

#include "PlayerCharacter.generated.h"

struct FInputActionValue;
struct FInventoryItem;
UCLASS()
class LAST_OASIS_API APlayerCharacter : public ACharacter,public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	APlayerCharacter();
	virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual void FellOutOfWorld(const class UDamageType& dmgType) override;
	
	UFUNCTION(BlueprintCallable,BlueprintImplementableEvent)
	void StartReduceStat();

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FTransform TentTransform;

protected:
	virtual void Tick(float DeltaSeconds) override;
	virtual void PossessedBy(AController* NewController) override;
	virtual void NotifyControllerChanged() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USpringArmComponent> CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UCameraComponent> FollowCamera;
	
protected:
	UPROPERTY(EditAnywhere, Category = GAS)
	TObjectPtr<class ULOAbilitySystemComponent> ASC;
	
//Anim
public:
	FORCEINLINE virtual class UAnimMontage* GetAttackMontage() const { return AttackMonatage; }
	FORCEINLINE virtual class UAnimMontage* GetDeadMontage() const { return DeadMontage; }
	void InputPressed(int32 InputID);

protected:
	UPROPERTY(EditAnywhere, Category = Anim)
	TObjectPtr<UAnimMontage> AttackMonatage;
	UPROPERTY(EditAnywhere, Category = Anim)
	TObjectPtr<UAnimMontage> DeadMontage;
//input
protected:
	UPROPERTY(EditAnywhere, Category = GAS)
	TArray<TSubclassOf<class UGameplayAbility>> StartAbilities;
	
	UPROPERTY(EditAnywhere, Category = GAS)
	TMap<int32, TSubclassOf<class UGameplayAbility>> StartInputAbilities;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputMappingContext> InputMappingContext;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> AttackAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> MoveAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> LookAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> Interaction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> ToggleCraft;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> ToggleInventory;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> ToggleMenu;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> ToggleMission;

private:
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void InputReleased(int32 InputID);
	void ToggleCraftFunction(const FInputActionValue& Value);
	void ToggleInventoryFunction(const FInputActionValue& Value);
	void InteractionFuction(const FInputActionValue& Value);
	void ToggleMissionFunction();

private:
	bool bIsInShadow;
	UPROPERTY()
	TObjectPtr<class ADirectionalLight> Sun;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	ALOPlayerController* LOPC;
public:

	virtual void BeginPlay() override;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	//TSubclassOf<UUserWidget> CraftingWidgetClass;
	
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	//TSubclassOf<UUserWidget> InventoryWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UCraftingWidget> CraftingWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crafting")
	TObjectPtr<ACraftingManager> CraftingManager;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UInventoryWidget> InventoryWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	TObjectPtr<AInventoryManager> InventoryManager;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	TArray<FInventoryItem> InventoryItems;


public:
	UFUNCTION(BlueprintCallable)
	void SetWeaponRange(int32 Value);
	UFUNCTION(BlueprintCallable)
	void EndHitCheck();
	UFUNCTION(BlueprintImplementableEvent,BlueprintCallable)
	void ShowEffect();
	UFUNCTION(BlueprintCallable,BlueprintImplementableEvent)
	void GetWeapon();
	void InitWidgetsFromHUD();

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	TSet<TObjectPtr<class AEnemyCh>> HitList;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	TObjectPtr<class UBoxComponent> WeaponRange1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	TObjectPtr<class UBoxComponent> WeaponRange2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	TObjectPtr<class UBoxComponent> WeaponRange3;
};