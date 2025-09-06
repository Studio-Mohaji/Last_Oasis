// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Data/DataAssetBase.h"
#include "RecipeState.generated.h"

USTRUCT(BlueprintType)
struct FRecipeState
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UDataAssetBase* RecipeItem; // ���� ������

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bUnlocked = false; // ��� ���� ����

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bCrafted = false;  // �̹� �����ߴ��� ����

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bAvailable = true; // ���� ���� �������� ����
};