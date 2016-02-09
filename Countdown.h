// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Countdown.generated.h"

UCLASS()
class TOPDOWN_HITMANCLEAN_API ACountdown : public AActor{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACountdown();
	~ACountdown();


	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	//===========================================

	// countdown timer value in seconds
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="TimerVariables")
	int32 CountdownTime;

/*	// Text to be rendered with countdown
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="TimerVariables")
	UTextRenderComponent* CountdownText;*/

	// Function to update the level timers display
	UFUNCTION(BlueprintCallable, Category="MyFunctions")
	void UpdateTimerDisplay();

	// function to advance the level timer
	UFUNCTION(BlueprintCallable,Category="MyFunctions")
	void AdvanceTimer();

	// function to perform action when level timer has completed
	UFUNCTION(BlueprintCallable,Category="MyFunctions")
	void CountdownHasFinished();

	/*UFUNCTION(BlueprintNativeEvent, Category="MyFunctions")
	void CountdownHasFinished_Implementation();// editable in bp*/

	// countdown timer handle supplied
	FTimerHandle CountdownTimerHandle;


};







