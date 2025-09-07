// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGameHUD.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Components/ProgressBar.h"
#include "GameMode/LOGameModeBase.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/CanvasPanelSlot.h"

void UInGameHUD::NativeConstruct()
{
	Super::NativeConstruct();

	SunTexture = LoadObject<UTexture2D>(nullptr, TEXT("/Game/Mireu/Data/Image/MagicalGirl_Sun.MagicalGirl_Sun"));
	MoonTexture = LoadObject<UTexture2D>(nullptr, TEXT("/Game/Mireu/Data/Image/MagicalGirl_DarkSun.MagicalGirl_DarkSun"));

	/*GoalTexts = {
	TEXT("û������ Ȱ���Ͽ� ���� ���ű⸦ �����ϼ���. ���ű�� �ٸ� �������� ��ġ�� �ľ��� �� �ִ� �߿� ����Դϴ�."),
	TEXT("���� ���ű⸦ ����Ͽ� �� �ٸ� �������� ��ġ�� �ľ��ϰ�, �װ����� ���ϼ���. ���ο� ������ ���� �� �������� �𸨴ϴ�."),
	TEXT("û������ Ȱ���Ͽ� ���� ��ȣ �ص��⸦ �����ϼ���. �ص���� ���� ���� �ü��� ��Ȯ�� ��ġ�� �� �� �ֽ��ϴ�."),
	TEXT("�� ���� �ʾҽ��ϴ�. ���� ���� �ü��� ���ϼ���.")
	};

	GoalBarTexts = {
		TEXT("���� ���ű� �����ϱ�"),
		TEXT("�ٸ� �����ҷ� ���ϱ�"),
		TEXT("���� ��ȣ �ص��� �����ϱ�"),
		TEXT("���� ���� �ü��� ���ϱ�")
	};*/

	InitProgress(Thirst, ThirstMID);
	InitProgress(Hunger, HungerMID);
	InitProgress(Temperature, TemperatureMID);

	UpdateTime(6, 0);
	UpdateDays(1);

	UpdateProgress(ThirstMID, 0.9f);
	UpdateProgress(HungerMID, 0.9f);
	UpdateProgress(TemperatureMID, 0.5f);

	SetGoalText(0);
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

void UInGameHUD::OnThirstChanged(const FOnAttributeChangeData& ChangeData)
{
	UpdateProgress(ThirstMID, ChangeData.NewValue / 100);

	FString NewText = FString::Printf(TEXT("%.1f"), ChangeData.NewValue);
	ThirstText->SetText(FText::FromString(NewText));
}

void UInGameHUD::OnHungerChanged(const FOnAttributeChangeData& ChangeData)
{
	UpdateProgress(HungerMID, ChangeData.NewValue/100);

	FString NewText = FString::Printf(TEXT("%.1f"), ChangeData.NewValue);
	HungerText->SetText(FText::FromString(NewText));
}

void UInGameHUD::OnTemperatureChanged(const FOnAttributeChangeData& ChangeData)
{
	UpdateProgress(TemperatureMID, ChangeData.NewValue/36.5 * 0.5);

	FString NewText = FString::Printf(TEXT("%.1f"), ChangeData.NewValue);
	TemperatureText->SetText(FText::FromString(NewText));
}

void UInGameHUD::UpdateTime(int32 Hour, int32 Minute)
{
	if (TimeText)
	{
		FString NewText = FString::Printf(TEXT("%d : %02d"), Hour, Minute);

		TimeText->SetText(FText::FromString(NewText));

		if(Day_Night)
		{
			if(Day_Night && ASC)
			{
				int TotalMinutes = Hour * 60 + Minute;

			
				if (TotalMinutes >= 6 * 60 && TotalMinutes < 20 * 60 + 24)
				{
					Day_Night->SetBrushFromTexture(SunTexture);
					if (ASC->HasMatchingGameplayTag(FGameplayTag::RequestGameplayTag("Game.Night")))
					{
						ASC->RemoveLooseGameplayTag(FGameplayTag::RequestGameplayTag("Game.Night"));
						ASC->AddLooseGameplayTag(FGameplayTag::RequestGameplayTag("Game.Day"));
						Day_Night->SetBrushFromTexture(SunTexture);
					}
				}
				else
				{
					Day_Night->SetBrushFromTexture(MoonTexture);
					if (ASC->HasMatchingGameplayTag(FGameplayTag::RequestGameplayTag("Game.Day")))
					{
						ASC->RemoveLooseGameplayTag(FGameplayTag::RequestGameplayTag("Game.Day"));
						ASC->AddLooseGameplayTag(FGameplayTag::RequestGameplayTag("Game.Night"));
						Day_Night->SetBrushFromTexture(MoonTexture);
					}
				}
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
		if (Days == 6 || Days == 12)
		{
			ASC->ApplyModToAttribute(ULOAttributeSet::GetLevelAttribute(),EGameplayModOp::Additive,1);
			FGameplayTagContainer Tag;
			Tag.AddTag(FGameplayTag::RequestGameplayTag("State.Reduction"));
			ASC->CancelAbilities(&Tag);
			ASC->TryActivateAbilitiesByTag(Tag);
		}
	}
}

void UInGameHUD::InitProgress(UImage*& State, UMaterialInstanceDynamic*& MID)
{	
	if (State && State->GetBrush().GetResourceObject())
	{
		MID = UMaterialInstanceDynamic::Create(
			Cast<UMaterialInterface>(State->GetBrush().GetResourceObject()),
			this
		);

		State->SetBrushFromMaterial(MID);
	}
}

void UInGameHUD::UpdateProgress(UMaterialInstanceDynamic*& MID, float Percent)
{
	if (MID)
	{
		MID->SetScalarParameterValue(FName("Percent"), Percent);
	}
}

void UInGameHUD::OpenGoal(bool bIsOpen)
{
	ElapsedTime = 0.f;
	TotalDuration = 3.0f;

	StartPos = UWidgetLayoutLibrary::SlotAsCanvasSlot(Goal)->GetPosition();

	EndPos = StartPos;
	EndPos.Y = bIsOpen ? -30 : 270;

	GetWorld()->GetTimerManager().SetTimer(BorderMoveTimerHandle, this, &UInGameHUD::UpdateBorderPosition, 0.01f, true);
}

void UInGameHUD::UpdateBorderPosition()
{
	if (!TargetBorder)
	{
		GetWorld()->GetTimerManager().ClearTimer(BorderMoveTimerHandle);
		return;
	}

	ElapsedTime += 0.01f;
	float Alpha = FMath::Clamp(ElapsedTime / TotalDuration, 0.f, 1.f);

	FVector2D NewPos = FMath::Lerp(StartPos, EndPos, Alpha);

	if (UCanvasPanelSlot* CanvasSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(Goal))
	{
		CanvasSlot->SetPosition(NewPos);
	}

	if (Alpha >= 1.f)
	{
		GetWorld()->GetTimerManager().ClearTimer(BorderMoveTimerHandle);
	}
}

void UInGameHUD::SetGoalText(int32 Phase)
{
	GoalBarText->SetText(FText::FromString(GoalBarTexts[Phase]));
	GoalText->SetText(FText::FromString(GoalTexts[Phase]));
}