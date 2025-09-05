// Copyright Epic Games, Inc. All Rights Reserved.

#include "Last_OasisGameMode.h"
#include "Last_OasisCharacter.h"
#include "UObject/ConstructorHelpers.h"

ALast_OasisGameMode::ALast_OasisGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
