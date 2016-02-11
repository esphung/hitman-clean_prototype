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



	//TSubclassOf<class ACountdown> DefaultCountdown = ACountdown::StaticClass();







	//"This is a message to yourself during runtime!"
	UE_LOG(YourLog,Warning,TEXT("GameMode object created."));

}// end null constructor

void ATopDown_HitmanCleanGameMode::BeginPlay(){
	Super::BeginPlay();

	// allows us to set user widgets that show up when the game starts
	ChangeMenuWidget(StartingWidgetClass);


	// instantiate default timer
	DefaultCountdown = ACountdown::StaticClass();

	ChangeCountdownTimer(StartingCountdownClass);



	// spawn actors from here
	UWorld* World = GetWorld();
	if (World){
		//World->SpawnActor<ACountdown>();
		World->SpawnActor<ACountdown>(DefaultCountdown);

	}
}// end begin play







void ATopDown_HitmanCleanGameMode::ChangeCountdownTimer(TSubclassOf<ACountdown> NewCountdownClass){

	if (CurrentCountdown != nullptr){
		//CurrentCountdown->RemoveFromViewport();
		CurrentCountdown = nullptr;
	}
	if (NewCountdownClass != nullptr){
		//CurrentCountdown = NewCountdownClass;
		if (CurrentCountdown != nullptr){
			//CurrentCountdown->AddToViewport();
		}
	}

}




void ATopDown_HitmanCleanGameMode::ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass){
	if (CurrentWidget != nullptr){
		CurrentWidget->RemoveFromViewport();
		CurrentWidget = nullptr;
	}
	if (NewWidgetClass != nullptr){
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), NewWidgetClass);
		if (CurrentWidget != nullptr){
			CurrentWidget->AddToViewport();
		}
	}
}




// destructor
ATopDown_HitmanCleanGameMode::~ATopDown_HitmanCleanGameMode(){
	//"This is a message to yourself during runtime!"
	UE_LOG(YourLog,Warning,TEXT("GameMode object destroyed."));
}