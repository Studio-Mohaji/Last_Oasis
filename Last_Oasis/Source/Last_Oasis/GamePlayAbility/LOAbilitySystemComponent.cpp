// Fill out your copyright notice in the Description page of Project Settings.


#include "GamePlayAbility/LOAbilitySystemComponent.h"

void ULOAbilitySystemComponent::InitializeComponent()
{
	Super::InitializeComponent();
	const ULOAttributeSet* AttrSet = GetSet<ULOAttributeSet>();
	if (!AttrSet)
	{
		return;
	}

}

void ULOAbilitySystemComponent::RemoveTagsByCategory(FGameplayTag CategoryTag)
{
	FGameplayTagContainer OwnedTags;
	GetOwnedGameplayTags(OwnedTags);

	TArray<FGameplayTag> TagsToRemove;
	for (auto Tag : OwnedTags)
	{
		if (Tag.MatchesTag(CategoryTag))
		{
			TagsToRemove.Add(Tag);
		}
	}

	for (auto& Tag : TagsToRemove)
	{
		RemoveLooseGameplayTag(Tag);
	}
}

void ULOAbilitySystemComponent::OnHealthChanged(const FOnAttributeChangeData& Data)
{
	if (Data.NewValue <= 0.f)
	{
		AddLooseGameplayTag(FGameplayTag::RequestGameplayTag("State.Dead"));
	}
}

void ULOAbilitySystemComponent::OnHungerChanged(const FOnAttributeChangeData& Data)
{
	if (Data.NewValue >= 90.f)
	{
		if (!HasMatchingGameplayTag(FGameplayTag::RequestGameplayTag("State.Hunger.Full")))
		{
			RemoveTagsByCategory(FGameplayTag::RequestGameplayTag("State.Hunger"));
			AddLooseGameplayTag(FGameplayTag::RequestGameplayTag("State.Hunger.Full"));
		}
	}
	else if (Data.NewValue <= 10.f)
	{
		if (!HasMatchingGameplayTag(FGameplayTag::RequestGameplayTag("State.Hunger.Fatigue")))
		{
			RemoveTagsByCategory(FGameplayTag::RequestGameplayTag("State.Hunger"));
			AddLooseGameplayTag(FGameplayTag::RequestGameplayTag("State.Hunger.Fatigue"));
		}
	}
	else if (Data.NewValue <= 0.f)
	{
		if (!HasMatchingGameplayTag(FGameplayTag::RequestGameplayTag("State.Thirst.Pain")))
		{
			RemoveTagsByCategory(FGameplayTag::RequestGameplayTag("State.Hunger"));
			AddLooseGameplayTag(FGameplayTag::RequestGameplayTag("State.Hunger.Pain"));
		}
	}
	else
	{
		if(!HasMatchingGameplayTag(FGameplayTag::RequestGameplayTag("State.Hunger")))
		{
			RemoveTagsByCategory(FGameplayTag::RequestGameplayTag("State.Hunger"));
		}
	}
}

void ULOAbilitySystemComponent::OnThirstChanged(const FOnAttributeChangeData& Data)
{
	if (Data.NewValue >= 70.f)
	{
		
		if (!HasMatchingGameplayTag(FGameplayTag::RequestGameplayTag("State.Thirst.Hydrated")))
		{
			RemoveTagsByCategory(FGameplayTag::RequestGameplayTag("State.Thirst"));
			AddLooseGameplayTag(FGameplayTag::RequestGameplayTag("State.Thirst.Hydrated"));
		}
	}
	else if (Data.NewValue <= 10.f)
	{
		if (!HasMatchingGameplayTag(FGameplayTag::RequestGameplayTag("State.Thirst.Fatigue")))
		{
			RemoveTagsByCategory(FGameplayTag::RequestGameplayTag("State.Thirst"));
			AddLooseGameplayTag(FGameplayTag::RequestGameplayTag("State.Thirst.Fatigue"));
		}
	}
	else if (Data.NewValue <= 0.f)
	{
		if (!HasMatchingGameplayTag(FGameplayTag::RequestGameplayTag("State.Thirst.Pain")))
		{
			RemoveTagsByCategory(FGameplayTag::RequestGameplayTag("State.Thirst"));
			AddLooseGameplayTag(FGameplayTag::RequestGameplayTag("State.Thirst.Pain"));
		}
	}
	else
	{
		if(!HasMatchingGameplayTag(FGameplayTag::RequestGameplayTag("State.Thirst")))
		{
			RemoveTagsByCategory(FGameplayTag::RequestGameplayTag("State.Thirst"));
		}
	}
}

void ULOAbilitySystemComponent::OnTemperatureChanged(const FOnAttributeChangeData& Data)
{
	if (Data.NewValue >= 35.f && Data.NewValue <= 38)
	{
		if(HasMatchingGameplayTag(FGameplayTag::RequestGameplayTag("State.Temperature")))
		{
			RemoveTagsByCategory(FGameplayTag::RequestGameplayTag("State.Temperature"));
		}
	}
	else if (Data.NewValue > 41.f)
	{
		if (!HasMatchingGameplayTag(FGameplayTag::RequestGameplayTag("State.Temperature.SevereHot")))
		{
			RemoveTagsByCategory(FGameplayTag::RequestGameplayTag("State.Temperature"));
			AddLooseGameplayTag(FGameplayTag::RequestGameplayTag("State.Temperature.SevereHot"));
			AddLooseGameplayTag(FGameplayTag::RequestGameplayTag("State.Temperature.ModerateHot"));
			AddLooseGameplayTag(FGameplayTag::RequestGameplayTag("State.Temperature.MildHot"));
		}
	}
	else if (Data.NewValue > 40.f)
	{
		if (!HasMatchingGameplayTag(FGameplayTag::RequestGameplayTag("State.Temperature.ModerateHot")))
		{
			RemoveTagsByCategory(FGameplayTag::RequestGameplayTag("State.Temperature"));
			AddLooseGameplayTag(FGameplayTag::RequestGameplayTag("State.Temperature.ModerateHot"));
			AddLooseGameplayTag(FGameplayTag::RequestGameplayTag("State.Temperature.MildHot"));
		}
	}
	else if (Data.NewValue > 38.f)
	{
		if (!HasMatchingGameplayTag(FGameplayTag::RequestGameplayTag("State.Temperature.MildHot")))
		{
			RemoveTagsByCategory(FGameplayTag::RequestGameplayTag("State.Temperature"));
			AddLooseGameplayTag(FGameplayTag::RequestGameplayTag("State.Temperature.MildHot"));
		}
	}
	else if (Data.NewValue < 32.f)
	{
		if (!HasMatchingGameplayTag(FGameplayTag::RequestGameplayTag("State.Temperature.SevereCold")))
		{
			RemoveTagsByCategory(FGameplayTag::RequestGameplayTag("State.Temperature"));
			AddLooseGameplayTag(FGameplayTag::RequestGameplayTag("State.Temperature.SevereCold"));
			AddLooseGameplayTag(FGameplayTag::RequestGameplayTag("State.Temperature.ModerateCold"));
			AddLooseGameplayTag(FGameplayTag::RequestGameplayTag("State.Temperature.MildCold"));
		}
	}
	else if (Data.NewValue < 33.f)
	{
		if (!HasMatchingGameplayTag(FGameplayTag::RequestGameplayTag("State.Temperature.ModerateCold")))
		{
			RemoveTagsByCategory(FGameplayTag::RequestGameplayTag("State.Temperature"));
			AddLooseGameplayTag(FGameplayTag::RequestGameplayTag("State.Temperature.ModerateCold"));
			AddLooseGameplayTag(FGameplayTag::RequestGameplayTag("State.Temperature.MildCold"));
		}
	}
	else if (Data.NewValue < 35.f)
	{
		if (!HasMatchingGameplayTag(FGameplayTag::RequestGameplayTag("State.Temperature.MildCold")))
		{
			RemoveTagsByCategory(FGameplayTag::RequestGameplayTag("State.Temperature"));
			AddLooseGameplayTag(FGameplayTag::RequestGameplayTag("State.Temperature.MildCold"));

		}
	}
	UE_LOG(LogTemp,Log,TEXT("%f"),Data.NewValue);
}
