// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/LOGameModeBase.h"

ALOGameModeBase::ALOGameModeBase()
{
    PrimaryActorTick.bCanEverTick = true;
}

void ALOGameModeBase::BeginPlay()
{
	Super::BeginPlay();
    
	//GetWorld()->GetTimerManager().SetTimer(TimeHandle, this, &ALOGameModeBase::UpdateGameTime, 1.0f, true);
}

void ALOGameModeBase::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
    ElapsedTime += DeltaSeconds;

    if (ElapsedTime > DayLength)
    {
        ElapsedTime -= DayLength; // 하루 리셋
    }

    CurrentHour = (ElapsedTime / DayLength) * 24.0f;

    int32 Hour = FMath::FloorToInt(CurrentHour);
    int32 Minute = FMath::FloorToInt((CurrentHour - Hour) * 60.0f);

    if (Minute != LastPrintedMinute)
    {
        LastPrintedMinute = Minute;
        UE_LOG(LogTemp, Log, TEXT("현재 게임 시각: %02d:%02d"), Hour, Minute);
    }
}

void ALOGameModeBase::SpawnBuilding()
{
    if (!GetWorld() || !BuildingA || !BuildingB || !BuildingC)
    {
        UE_LOG(LogTemp, Warning, TEXT("World or Building Classes not set!"));
        return;
    }

    FVector LocationA;
    FVector LocationB;
    FVector LocationC;
    
    const float MinDistanceBetweenBuildings = 3 * Length / 5.0f;
    const float MinDistanceToEdge = Length / 8.0f;

    const int MaxTries = 500; // 좌표 찾기 시도 횟수 제한

    bool bFoundValid = false;

    while (!bFoundValid)
    {
        int TryCount = 0;

        LocationA.X = FMath::RandRange(Center.X - Length/2 + MinDistanceToEdge, Center.X + Length/2 - MinDistanceToEdge);
        LocationA.Y = FMath::RandRange(Center.Y - Length/2 + MinDistanceToEdge, Center.Y + Length/2 - MinDistanceToEdge);
        LocationA.Z = 0;

        bool bValidB = false;
        while (!bValidB && TryCount < MaxTries)
        {
            LocationB.X = FMath::RandRange(Center.X - Length/2 + MinDistanceToEdge, Center.X + Length/2 - MinDistanceToEdge);
            LocationB.Y = FMath::RandRange(Center.Y - Length/2 + MinDistanceToEdge, Center.Y + Length/2 - MinDistanceToEdge);
            LocationB.Z = 0;

            if (FVector::Dist(LocationB, LocationA) >= MinDistanceBetweenBuildings)
            {
                bValidB = true;
            }
            else
            {
                TryCount++;
            }
        }

        if (!bValidB)
        {
            UE_LOG(LogTemp, Warning, TEXT("B 위치 찾기 실패 → A부터 다시 시도"));
            continue;
        }

        bool bValidC = false;
        TryCount = 0;
        while (!bValidC && TryCount < MaxTries)
        {
            LocationC.X = FMath::RandRange(Center.X - Length/2 + MinDistanceToEdge, Center.X + Length/2 - MinDistanceToEdge);
            LocationC.Y = FMath::RandRange(Center.Y - Length/2 + MinDistanceToEdge, Center.Y + Length/2 - MinDistanceToEdge);
            LocationC.Z = 0;

            if (FVector::Dist(LocationC, LocationA) >= MinDistanceBetweenBuildings &&
                FVector::Dist(LocationC, LocationB) >= MinDistanceBetweenBuildings)
            {
                bValidC = true;
            }
            else
            {
                TryCount++;
            }
        }

        if (!bValidC)
        {
            UE_LOG(LogTemp, Warning, TEXT("C 위치 찾기 실패 → A부터 다시 시도"));
            continue;
        }
        bFoundValid = true;
    }

    GetWorld()->SpawnActor<AActor>(BuildingA, LocationA, FRotator::ZeroRotator);
    GetWorld()->SpawnActor<AActor>(BuildingB, LocationB, FRotator::ZeroRotator);
    GetWorld()->SpawnActor<AActor>(BuildingC, LocationC, FRotator::ZeroRotator);
}

void ALOGameModeBase::UpdateGameTime()
{
	ElapsedTime += 1.0f;

	if (ElapsedTime > DayLength)
	{
		ElapsedTime -= DayLength;
	}
	CurrentHour = (ElapsedTime / DayLength) * 24.0f;

	int32 Hour = FMath::FloorToInt(CurrentHour);
	int32 Minute = FMath::FloorToInt((CurrentHour - Hour) * 60.0f);
    if (Minute % 5 == 0 && FMath::IsNearlyZero(FMath::Frac(CurrentHour * 60.0f)))
    {
        UE_LOG(LogTemp, Log, TEXT("현재 게임 시각: %02d:%02d"), Hour, Minute);
    }

}

