// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/LOGameModeBase.h"
#include "Engine/DirectionalLight.h"
#include "Kismet/GameplayStatics.h"
#include "UI/InGameHUD.h"
#include "EngineUtils.h"
#include "Math/UnrealMathUtility.h"
#include "Actor/BuildingPoint.h"

ALOGameModeBase::ALOGameModeBase()
{
    PrimaryActorTick.bCanEverTick = true;
}

void ALOGameModeBase::Respawn()
{
    APlayerController* Controller = GetWorld()->GetFirstPlayerController();
    if (Controller)
    {
        APawn* NewPawn = SpawnDefaultPawnAtTransform(Controller, SpawnPoint);
        if (NewPawn)
        {
            Controller->Possess(NewPawn);
        }
    }
}

void ALOGameModeBase::SetSpawnPoint(FTransform SpawnTransform)
{
    SpawnPoint = SpawnTransform;
    SpawnPoint += FTransform(FVector(0, -500, 0));
}

void ALOGameModeBase::BeginPlay()
{
	Super::BeginPlay();
    Sun = Cast<ADirectionalLight>(UGameplayStatics::GetActorOfClass(GetWorld(), ADirectionalLight::StaticClass()));
    ElapsedTime = (6.0f / 24.0f) * DayLength;
	//GetWorld()->GetTimerManager().SetTimer(TimeHandle, this, &ALOGameModeBase::UpdateGameTime, 1.0f, true);

    PC = Cast<ALOPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
        
	FTimerHandle dummyHandle;
    //GetWorld()->GetTimerManager().SetTimer(dummyHandle, this, &ALOGameModeBase::SpawnBuilding, 5.0f, false);
	SpawnBuilding();
}

void ALOGameModeBase::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
    ElapsedTime += DeltaSeconds;

    if (ElapsedTime > DayLength)
    {
        ElapsedTime -= DayLength;

        Days++;
        if (PC->HUD)
        {
            PC->HUD->UpdateDays(Days);
        }
    }

    CurrentHour = (ElapsedTime / DayLength) * 24.0f;

    int32 Hour = FMath::FloorToInt(CurrentHour);
    int32 Minute = FMath::FloorToInt((CurrentHour - Hour) * 60.0f);

    if (Minute != LastPrintedMinute)
    {
        LastPrintedMinute = Minute;
		
        if(PC->HUD)
        {
            PC->HUD->UpdateTime(Hour, Minute);
		}
    }
    if (Sun == nullptr) return;

    float Pitch = (CurrentHour / 24.0f) * 360.0f - 90.0f;

    FRotator NewRotation(-Pitch, -90.0f, 0.0f);
    Sun->SetActorRotation(NewRotation);
}

void ALOGameModeBase::SpawnBuilding()
{
    TArray<AActor*> FoundActors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABuildingPoint::StaticClass(), FoundActors);
    
    if (!GetWorld() || !PC || !PC->HUD || FoundActors.Num() < 3)
    {
        UE_LOG(LogTemp, Warning, TEXT("Build"));

        GetWorld()->GetTimerManager().SetTimer(HUDCheckTimerHandle, this, &ALOGameModeBase::SpawnBuilding, 0.1f, false);
        return;
    }
    
    UE_LOG(LogTemp, Warning, TEXT("Build Start"));

	TArray<FVector> Locations;
  
    UE_LOG(LogTemp, Warning, TEXT("Build %d"), FoundActors.Num());

    for (int32 i = 0; i < FoundActors.Num(); ++i)
    {
        int32 SwapIndex = FMath::RandRange(i, FoundActors.Num() - 1);
        FoundActors.Swap(i, SwapIndex);
    }

    //Result
    AActor* LaboA = nullptr;

    for (int32 i = 0; i < 3; ++i)
    {
        UE_LOG(LogTemp, Warning, TEXT("Build add"));
		Locations.Add(FoundActors[i]->GetActorLocation());

        if (i == 0 && BuildingA)
        {
            LaboA = GetWorld()->SpawnActor<AActor>(BuildingA, Locations[0], FRotator::ZeroRotator);
        }
        else if (i == 1 && BuildingB)
        {
            GetWorld()->SpawnActor<AActor>(BuildingB, Locations[1], FRotator::ZeroRotator);
        }
        else if (i == 2 && BuildingC)
        {
            GetWorld()->SpawnActor<AActor>(BuildingC, Locations[2], FRotator::ZeroRotator);
		}
    }

    SpawnPoint = LaboA->GetActorTransform();
    SpawnPoint += FTransform(FVector(0, -1000, +200));
    APlayerController* Controller = GetWorld()->GetFirstPlayerController();
    if (Controller)
    {
        Controller->GetPawn()->SetActorTransform(SpawnPoint);
    }
    
    if (PC->HUD)
    {
		UE_LOG(LogTemp, Warning, TEXT("SetBuilding"));
        PC->HUD->SetBuildings(PC->GetPawn<APlayerCharacter>(), Locations[0], Locations[1], Locations[2]);
	}
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("NoHUD"));
	}
}

void ALOGameModeBase::UpdateGameTime()
{
	ElapsedTime += 1.0f;

	if (ElapsedTime > DayLength)
	{
		ElapsedTime -= DayLength;
	}
	CurrentHour = (ElapsedTime / DayLength) * 24.0f;
}

