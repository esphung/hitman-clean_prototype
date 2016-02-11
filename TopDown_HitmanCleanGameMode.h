// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
#pragma once

#include "Countdown.h"
#include "Blueprint/UserWidget.h"//
#include "GameFramework/GameMode.h"
#include "TopDown_HitmanCleanGameMode.generated.h"

UCLASS(minimalapi)
class ATopDown_HitmanCleanGameMode : public AGameMode{
	GENERATED_BODY()

public:
	ATopDown_HitmanCleanGameMode();
	~ATopDown_HitmanCleanGameMode();


public:
	/** Called when the game starts. */
	virtual void BeginPlay() override;

	/** Remove the current menu widget and create a new one from the specified class, if provided. */
	UFUNCTION(BlueprintCallable, Category = "UMG Game")
	void ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass);

	/* REmove current timer and create a new one */
	UFUNCTION(BlueprintCallable, Category = "Countdown Game")
	void ChangeCountdownTimer(TSubclassOf<ACountdown> NewCountdownClass);

protected:
	/** The widget class we will use as our menu when the game starts. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG Game")
	TSubclassOf<UUserWidget> StartingWidgetClass;//

	/** The widget instance that we are using as our menu. */
	UPROPERTY()
	UUserWidget* CurrentWidget;

	/** The widget class we will use as our menu when the game starts. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Countdown Timer")
	TSubclassOf<ACountdown> StartingCountdownClass;//

	/* Timer for level if any */
	UPROPERTY()
	ACountdown* CurrentCountdown;



};



