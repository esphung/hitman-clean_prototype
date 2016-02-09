// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.



#include "TopDown_HitmanClean.h"
#include "TopDown_HitmanCleanGameMode.h"
#include "TopDown_HitmanCleanPlayerController.h"
#include "TopDown_HitmanCleanCharacter.h"
#include "Countdown.h"

ATopDown_HitmanCleanGameMode::ATopDown_HitmanCleanGameMode(){
	// use our custom PlayerController class
	PlayerControllerClass = ATopDown_HitmanCleanPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter_BP"));
	if (PlayerPawnBPClass.Class != NULL){
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}





	//"This is a message to yourself during runtime!"
	UE_LOG(YourLog,Warning,TEXT("GameMode object created."));

}

ATopDown_HitmanCleanGameMode::~ATopDown_HitmanCleanGameMode(){
//"This is a message to yourself during runtime!"
	UE_LOG(YourLog,Warning,TEXT("GameMode object destroyed."));
}