// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "TopDown_HitmanClean.h"
#include "TopDown_HitmanCleanPlayerController.h"
#include "AI/Navigation/NavigationSystem.h"

ATopDown_HitmanCleanPlayerController::ATopDown_HitmanCleanPlayerController(){
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}

void ATopDown_HitmanCleanPlayerController::PlayerTick(float DeltaTime){
	Super::PlayerTick(DeltaTime);

	// keep updating the destination every tick while desired
	if (bMoveToMouseCursor){
		MoveToMouseCursor();
	}
}

void ATopDown_HitmanCleanPlayerController::SetupInputComponent(){
	// set up gameplay key bindings
	Super::SetupInputComponent();

	InputComponent->BindAction("SetDestination", IE_Pressed, this, &ATopDown_HitmanCleanPlayerController::OnSetDestinationPressed);
	InputComponent->BindAction("SetDestination", IE_Released, this, &ATopDown_HitmanCleanPlayerController::OnSetDestinationReleased);

	// support touch devices
	InputComponent->BindTouch(EInputEvent::IE_Pressed, this, &ATopDown_HitmanCleanPlayerController::MoveToTouchLocation);
	InputComponent->BindTouch(EInputEvent::IE_Repeat, this, &ATopDown_HitmanCleanPlayerController::MoveToTouchLocation);
}

void ATopDown_HitmanCleanPlayerController::MoveToMouseCursor(){
	// Trace to see what is under the mouse cursor
	FHitResult Hit;
	GetHitResultUnderCursor(ECC_Visibility, false, Hit);

	if (Hit.bBlockingHit){
		// We hit something, move there
		SetNewMoveDestination(Hit.ImpactPoint);
	}
}

void ATopDown_HitmanCleanPlayerController::MoveToTouchLocation(const ETouchIndex::Type FingerIndex, const FVector Location){
	FVector2D ScreenSpaceLocation(Location);

	// Trace to see what is under the touch location
	FHitResult HitResult;
	GetHitResultAtScreenPosition(ScreenSpaceLocation, CurrentClickTraceChannel, true, HitResult);
	if (HitResult.bBlockingHit){
		// We hit something, move there
		SetNewMoveDestination(HitResult.ImpactPoint);
	}
}

void ATopDown_HitmanCleanPlayerController::SetNewMoveDestination(const FVector DestLocation){
	APawn* const Pawn = GetPawn();
	if (Pawn){
		UNavigationSystem* const NavSys = GetWorld()->GetNavigationSystem();
		float const Distance = FVector::Dist(DestLocation, Pawn->GetActorLocation());

		// We need to issue move command only if far enough in order for walk animation to play correctly
		if (NavSys && (Distance > 120.0f)){
			NavSys->SimpleMoveToLocation(this, DestLocation);
		}
	}
}

void ATopDown_HitmanCleanPlayerController::OnSetDestinationPressed(){
	// set flag to keep updating destination until released
	bMoveToMouseCursor = true;
}

void ATopDown_HitmanCleanPlayerController::OnSetDestinationReleased(){
	// clear flag to indicate we should stop updating the destination
	bMoveToMouseCursor = false;
}
