// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/LOPlayerController.h"
#include "UI/InGameHUD.h"

void ALOPlayerController::InitHUD()
{
	if (HUDWidgetClass)
	{
		HUD = CreateWidget<UInGameHUD>(this, HUDWidgetClass);
		if (HUD)
		{
			HUD->AddToViewport();
			HUD->SetAbilitySystemComponent();
		}
	}
}

void ALOPlayerController::BeginPlay()
{
	Super::BeginPlay();
	

}
