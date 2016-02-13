// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "PickUp.generated.h"

UCLASS()
class TOPDOWN_HITMANCLEAN_API APickUp : public AActor {
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APickUp();

	/* Give the pick up item a name */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item Name")
	FString ItemNameText;


	// pick up logic variables
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="PickUpLogic")
	bool is_near_player;

	/* True when item is able to be picked up, false if it is deactivated */
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="PickUpLogic")
	bool isActive;

	/* Simple primitive collision component used as root */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="PickUpCollision")
	USphereComponent* BaseCollisionComponent;

	/* static mesh component */
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="PickUpMesh")
	UStaticMeshComponent* PickUpMesh;

	/* function to call when the pick up item is collected */
/*	UFUNCTION(BlueprintNativeEvent)
	void OnPickedUp();*/


	/** called when something enters the sphere component */
	UFUNCTION()
	virtual void OnOverlapBegin(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	/** called when something leaves the sphere component */
	UFUNCTION()
	virtual void OnOverlapEnd(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	// override this function
	UFUNCTION(BlueprintCallable,Category="ItemInteraction")
	void PickedUp();

	UFUNCTION(BlueprintCallable,Category="ItemInteraction")
	FString GetMyNameString();




};
