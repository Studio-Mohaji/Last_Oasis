// MyGameMode.cpp
#include "Last_OasisGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Math/UnrealMathUtility.h"

USTRUCT(BlueprintType)
struct FSpawnResult
{
    FVector LocationA;
    FVector LocationB;
    FVector LocationC;
};

void ALast_OasisGameMode::SpawnBuilding(const FVector& Center, float L)
{
       if (!GetWorld() || !ClassA || !ClassB || !ClassC)
    {
        UE_LOG(LogTemp, Warning, TEXT("World or Building Classes not set!"));
        return;
    }

    FVector LocationA;
    FVector LocationB;
    FVector LocationC;
    
    const float MinDistanceBetweenBuildings = 2 * L / 5.0f;
    const float MinDistanceToEdge = L / 8.0f;

    const int MaxTries = 500; // 좌표 찾기 시도 횟수 제한

    bool bFoundValid = false;

    while (!bFoundValid)
    {
        int TryCount = 0;

        // A 좌표 찾기
        LocationA.X = FMath::RandRange(Center.X - L/2 + MinDistanceToEdge, Center.X + L/2 - MinDistanceToEdge);
        LocationA.Y = FMath::RandRange(Center.Y - L/2 + MinDistanceToEdge, Center.Y + L/2 - MinDistanceToEdge);
        LocationA.Z = 0;

        // B 좌표 찾기
        bool bValidB = false;
        while (!bValidB && TryCount < MaxTries)
        {
            LocationB.X = FMath::RandRange(Center.X - L/2 + MinDistanceToEdge, Center.X + L/2 - MinDistanceToEdge);
            LocationB.Y = FMath::RandRange(Center.Y - L/2 + MinDistanceToEdge, Center.Y + L/2 - MinDistanceToEdge);
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
            continue; // 다시 A부터 뽑기
        }

        // C 좌표 찾기
        bool bValidC = false;
        TryCount = 0;
        while (!bValidC && TryCount < MaxTries)
        {
            LocationC.X = FMath::RandRange(Center.X - L/2 + MinDistanceToEdge, Center.X + L/2 - MinDistanceToEdge);
            LocationC.Y = FMath::RandRange(Center.Y - L/2 + MinDistanceToEdge, Center.Y + L/2 - MinDistanceToEdge);
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
            continue; // 다시 A부터 뽑기
        }

        // A, B, C 전부 성공
        bFoundValid = true;
    }

    // ===== 세 좌표가 전부 확정된 후 스폰 =====
    GetWorld()->SpawnActor<AActor>(ClassA, LocationA, FRotator::ZeroRotator);
    GetWorld()->SpawnActor<AActor>(ClassB, LocationB, FRotator::ZeroRotator);
    GetWorld()->SpawnActor<AActor>(ClassC, LocationC, FRotator::ZeroRotator);
}

void ALast_OasisGameMode::BeginPlay()
{
    Super::BeginPlay();
    
}