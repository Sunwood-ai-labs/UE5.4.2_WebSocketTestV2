// Copyright Epic Games, Inc. All Rights Reserved.

#include "WebSocketTestV2GameMode.h"
#include "WebSocketTestV2Character.h"
#include "UObject/ConstructorHelpers.h"

AWebSocketTestV2GameMode::AWebSocketTestV2GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
