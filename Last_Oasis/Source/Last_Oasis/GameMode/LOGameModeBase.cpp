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
            AddMinute(360);
        }
    }
}

    void ALOGameModeBase::SetSpawnPoint(FTransform SpawnTransform)
{
    SpawnPoint = SpawnTransform;
    SpawnPoint += FTransform(FVector(0,-500,0));
    SpawnPoint.SetScale3D(FVector(1,1,1));
}

void ALOGameModeBase::SetTimeOfDay(int32 NewHour, int32 NewMinute)
{
    NewHour = FMath::Clamp(NewHour, 0, 23);
    NewMinute = FMath::Clamp(NewMinute, 0, 59);

    float TargetHour = NewHour + (NewMinute / 60.0f);

    float CurrentHourNow = (ElapsedTime / DayLength) * 24.0f;

    if (CurrentHourNow < 12.0f && TargetHour >= 0.0f)
    {
        Days++;
        if (PC && PC->HUD)
        {
            PC->HUD->UpdateDays(Days);
        }
    }

    ElapsedTime = (TargetHour / 24.0f) * DayLength;

    CurrentHour = TargetHour;

    if (Sun)
    {
        float Pitch = (CurrentHour / 24.0f) * 360.0f - 90.0f;
        FRotator NewRotation(-Pitch, -90.0f, 0.0f);
        Sun->SetActorRotation(NewRotation);
    }

    if (PC && PC->HUD)
    {
        PC->HUD->UpdateTime(NewHour, NewMinute);
    }
}

bool ALOGameModeBase::GetRemainTimeUntilMorning()
{
    float NextMorning = 6.0f;
    float TimeLeft;

    if (CurrentHour < NextMorning)
    {
        TimeLeft = NextMorning - CurrentHour;
    }
    else
    {
        TimeLeft = 24.0f - CurrentHour + NextMorning;
    }
    return TimeLeft >= 5.0f;
}

void ALOGameModeBase::AddMinute(int32 AddMinute)
{
    if (AddMinute <= 0) return;

    float HoursToAdd = AddMinute / 60.0f;

    float TimeToAdd = (HoursToAdd / 24.0f) * DayLength;

    ElapsedTime += TimeToAdd;

    if (ElapsedTime > DayLength)
    {
        ElapsedTime -= DayLength;
        Days++;

        if (PC && PC->HUD)
        {
            PC->HUD->UpdateDays(Days);
        }
    }

    CurrentHour = (ElapsedTime / DayLength) * 24.0f;
    int32 Hour = FMath::FloorToInt(CurrentHour);
    int32 Minute = FMath::FloorToInt((CurrentHour - Hour) * 60.0f);

    if (Sun)
    {
        float Pitch = (CurrentHour / 24.0f) * 360.0f - 90.0f;
        FRotator NewRotation(-Pitch, -90.0f, 0.0f);
        Sun->SetActorRotation(NewRotation);
    }

    if (PC && PC->HUD)
    {
        PC->HUD->UpdateTime(Hour, Minute);
    }
}

void ALOGameModeBase::BeginPlay()
{
	Super::BeginPlay();
    Sun = Cast<ADirectionalLight>(UGameplayStatics::GetActorOfClass(GetWorld(), ADirectionalLight::StaticClass()));
    ElapsedTime = (6.0f / 24.0f) * DayLength;
	//GetWorld()->GetTimerManager().SetTimer(TimeHandle, this, &ALOGameModeBase::UpdateGameTime, 1.0f, true);

    PC = Cast<ALOPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
        
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

    TArray<FVector> Locations;

    UE_LOG(LogTemp, Warning, TEXT("Build %d"), FoundActors.Num());

    for (int32 i = 0; i < FoundActors.Num(); ++i)
    {
        int32 SwapIndex = FMath::RandRange(i, FoundActors.Num() - 1);
        FoundActors.Swap(i, SwapIndex);
    }

    AActor* LaboA = nullptr;

    for (int32 i = 0; i < 3; ++i)
    {
        Locations.Add(FoundActors[i]->GetActorLocation());

        AActor* Spawned = nullptr;

        if (i == 0 && BuildingA)
        {
            LaboA = GetWorld()->SpawnActor<AActor>(BuildingA, Locations[0], FRotator::ZeroRotator);
        }
        else if (i == 1 && BuildingB)
        {
            Spawned = GetWorld()->SpawnActor<AActor>(BuildingB, Locations[1], FRotator::ZeroRotator);
        }
        else if (i == 2 && BuildingC)
        {
            Spawned = GetWorld()->SpawnActor<AActor>(BuildingC, Locations[2], FRotator::ZeroRotator);
        }

        if (Spawned)
        {
            SpawnedBuildings.Add(Spawned);
        }
    }

    SpawnPoint = LaboA->GetActorTransform();
    SpawnPoint += FTransform(FVector(0, -1000, +200));

	SpawnPoint.SetScale3D(FVector(1, 1, 1));

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

