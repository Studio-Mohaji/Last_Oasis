// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AbilitySystemInterface.h"
#include "GamePlayAbility/AttributeSet/LOAttributeSet.h"
#include "Components/Border.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Widget/InventoryWidget.h"
#include "Widget/CraftingWidget.h"
#include "InGameHUD.generated.h"

UCLASS()
class LAST_OASIS_API UInGameHUD : public UUserWidget, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	void SetAbilitySystemComponent();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

protected:
	virtual void NativeConstruct() override;

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
	

	UPROPERTY(EditAnywhere, Meta = (AllowPrivateAccess = true, BindWidget))
	TObjectPtr<class UTextBlock> DaysText;

	UPROPERTY(EditAnywhere, Meta = (AllowPrivateAccess = true, BindWidget))
	TObjectPtr<class UImage> Day_Night;

	UPROPERTY(EditAnywhere, Meta = (AllowPrivateAccess = true, BindWidget))
	TObjectPtr<class UTextBlock> TimeText;

	UPROPERTY(EditAnywhere, Meta = (AllowPrivateAccess = true, BindWidget))
	TObjectPtr<class UImage> Raider;

	UPROPERTY(EditAnywhere, Meta = (AllowPrivateAccess = true, BindWidget))
	TObjectPtr<class UBorder> Goal;

	UPROPERTY(EditAnywhere, Meta = (AllowPrivateAccess = true, BindWidget))
	TObjectPtr<class UTextBlock> GoalText;

	UPROPERTY(EditAnywhere, Meta = (AllowPrivateAccess = true, BindWidget))
	TObjectPtr<class UImage> GoalImg;

	UPROPERTY(EditAnywhere, Meta = (AllowPrivateAccess = true, BindWidget))
	TObjectPtr<class UTextBlock> GoalBarText;

	UPROPERTY(EditAnywhere, Meta = (AllowPrivateAccess = true, BindWidget))
	TObjectPtr<class UImage> Inventory;

	UPROPERTY(EditAnywhere, Meta = (AllowPrivateAccess = true, BindWidget))
	TObjectPtr<class UImage> Crafting;

	UTexture2D* SunTexture;
	UTexture2D* MoonTexture;

	UPROPERTY(EditAnywhere, Meta = (AllowPrivateAccess = true, BindWidget))
	TObjectPtr<class UInventoryWidget> InventoryWidget;

	UPROPERTY(EditAnywhere, Meta = (AllowPrivateAccess = true, BindWidget))
	TObjectPtr<class UCraftingWidget> CraftingWidget;

public:
	UFUNCTION(BlueprintCallable, Category = "UI")
	UInventoryWidget* GetInventoryWidget() const { return InventoryWidget; }

	UFUNCTION(BlueprintCallable, Category = "UI")
	UCraftingWidget* GetCraftingWidget() const { return CraftingWidget; }

public:
	UFUNCTION()
	void UpdateTime(int32 Hour, int32 Minute);

	UFUNCTION()
	void UpdateDays(int32 Days);
};
