// Copyright Epic Games, Inc. All Rights Reserved.

#include "FlingSwingWingGameMode.h"
#include "FlingSwingWingCharacter.h"
#include "UObject/ConstructorHelpers.h"

AFlingSwingWingGameMode::AFlingSwingWingGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
