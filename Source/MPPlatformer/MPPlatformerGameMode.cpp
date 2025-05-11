// Copyright Epic Games, Inc. All Rights Reserved.

#include "MPPlatformerGameMode.h"
#include "MPPlatformerCharacter.h"
#include "UObject/ConstructorHelpers.h"

AMPPlatformerGameMode::AMPPlatformerGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
