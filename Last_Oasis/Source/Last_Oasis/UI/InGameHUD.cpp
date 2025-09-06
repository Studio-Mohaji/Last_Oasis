// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGameHUD.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Components/ProgressBar.h"
#include "GameMode/LOGameModeBase.h"

void UInGameHUD::NativeConstruct()
{
	Super::NativeConstruct();

	SunTexture = LoadObject<UTexture2D>(nullptr, TEXT("/Game/Mireu/Data/Image/MagicalGirl_Sun.MagicalGirl_Sun"));
	MoonTexture = LoadObject<UTexture2D>(nullptr, TEXT("/Game/Mireu/Data/Image/MagicalGirl_DarkSun.MagicalGirl_DarkSun"));

	UpdateTime(6, 0);
	UpdateDays(1);
}

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

void UInGameHUD::UpdateTime(int32 Hour, int32 Minute)
{
	if (TimeText)
	{
		FString NewText = FString::Printf(TEXT("%d : %02d"), Hour, Minute);

		TimeText->SetText(FText::FromString(NewText));

		if(Day_Night)
		{
			int TotalMinutes = Hour * 60 + Minute;

			if (TotalMinutes >= 6 * 60 && TotalMinutes < 20 * 60 + 24)
			{
				Day_Night->SetBrushFromTexture(SunTexture);
			}
			else
			{
				Day_Night->SetBrushFromTexture(MoonTexture);
			}
		}
	}
}

void UInGameHUD::UpdateDays(int32 Days)
{
	if(DaysText)
	{
		FString NewText = FString::Printf(TEXT("%d Days"), Days);

		DaysText->SetText(FText::FromString(NewText));
	}
}