// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Data/DataAssetBase.h"
#include "../Data/ResourceDataAsset.h"
#include "RecipeState.generated.h"

USTRUCT(BlueprintType)
struct FRecipeResource
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UDataAssetBase* Resource; // ��� ����

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 NeedCount; // �ʿ��� ����
};

USTRUCT(BlueprintType)
struct FRecipeState
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UDataAssetBase* RecipeItem; // ���� ������

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FRecipeResource> RequiredResources; // �ʿ��� �ڿ� 
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bUnlocked = false; // ��� ���� ����

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bCrafted = false;  // �̹� �����ߴ��� ����

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bAvailable = true; // ���� ���� �������� ����
};