// Fill out your copyright notice in the Description page of Project Settings.

#include "TopDown_HitmanClean.h"
#include "Countdown.h"

// Sets default values
ACountdown::ACountdown(){
 	// Set this actor to call Tick() every frame.  You can turn this off to improve per formance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// set default values for level countdown timer
	CountdownText = CreateDefaultSubobject<UTextRenderComponent>(
		TEXT("CountdownNumber"));
	CountdownText->SetHorizontalAlignment(EHTA_Center);
	CountdownText->SetWorldSize(150.0f);
	RootComponent = CountdownText;

	// measured in seconds
	CountdownTime = 300;// 5min

	UE_LOG(YourLog,Warning,TEXT("Countdown object created."));
}

ACountdown::~ACountdown(){
	UE_LOG(YourLog,Warning,TEXT("Countdown object destroyed."));
}


// Called when the game starts or when spawned
void ACountdown::BeginPlay(){
	Super::BeginPlay();
	UpdateTimerDisplay();
	GetWorldTimerManager().SetTimer(CountdownTimerHandle, this, &ACountdown::AdvanceTimer, 1.0f, true);

}

// Called every frame
void ACountdown::Tick( float DeltaTime ){
	Super::Tick( DeltaTime );

}

void ACountdown::UpdateTimerDisplay(){
	CountdownText->SetText(FString::FromInt(FMath::Max(CountdownTime, 0)));
	UE_LOG(YourLog,Warning,TEXT("CountdownTime is %d"), CountdownTime);

}




void ACountdown::AdvanceTimer(){
    --CountdownTime;
    UpdateTimerDisplay();
    if (CountdownTime < 1){
        //We're done counting down, so stop running the timer.
        GetWorldTimerManager().ClearTimer(CountdownTimerHandle);
        CountdownHasFinished();
    }
}

void ACountdown::CountdownHasFinished(){
	//Change to a special readout
	CountdownText->SetText(TEXT("Game Over!"));
	UE_LOG(YourLog,Warning,TEXT("CountdownTime is Finished.  Game Over!"));
}



/*

void ACountdown::CountdownHasFinished_Implementation(){
	// do this in blueprints when countdown has finished
}*/