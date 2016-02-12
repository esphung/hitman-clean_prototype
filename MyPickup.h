// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "MyPickup.generated.h"

UCLASS()
class TOPDOWN_HITMANCLEAN_API AMyPickup : public AActor{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMyPickup();

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Pickup)
	UCapsuleComponent* BaseCollisionComponent;

	/** StaticMeshComponent to represent the pickup in the level */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Pickup)
	UStaticMeshComponent* PickupMesh;

	UFUNCTION()
	virtual void OnOverlapBegin(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};