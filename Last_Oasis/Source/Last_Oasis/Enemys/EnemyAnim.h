
#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "EnemyAnim.generated.h"

UCLASS()
class LAST_OASIS_API UEnemyAnim : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 AnimStateIdx;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bCanAttack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsDead;
};
