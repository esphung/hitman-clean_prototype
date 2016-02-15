// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TopDown_HitmanCleanCharacter.h"
#include "PickUp.h"
#include "GameFramework/Actor.h"
#include "DepositBase.generated.h"

UCLASS()
class TOPDOWN_HITMANCLEAN_API ADepositBase : public AActor{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADepositBase();

/*	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="DepositBaseVariables")
	ATopDown_HitmanCleanCharacter* OtherCharacter;*/

	// Text to be rendered with depositBase
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="DepositBaseVariables")
	UTextRenderComponent* VisibleDepositBaseText;

	// depositBase instance's name
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="DepositBaseVariables")
	FString my_name_string;

	// string used to clear out text displayed
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="DepositBaseVariables")
	FString clear_text_string;

	// current text string displayed
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="DepositBaseVariables")
	FString current_text_string;

	// text when interacting with player
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="DepositBaseVariables")
	FString interaction_text_string;

	// text shown when player needs to find an item
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="DepositBaseVariables")
	FString find_item_text_string;

	// text shown when depositBase is full
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="DepositBaseVariables")
	FString deposit_full_text_string;

	// logic value when depositBase has been found by the player
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="DepositBaseVariables")
	bool is_found_by_player;

	// current amount of items the depositBase is holding
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="DepositBaseVariables")
	int32 my_current_items_value;

	// maximum amount of items the depositBase can hold
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="DepositBaseVariables")
	int32 my_maximum_items_value;

	// checks if depositBase is full
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="DepositBaseVariables")
	bool is_deposit_full;



	/* Simple primitive collision component used as root */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="PickUpCollision")
	USphereComponent* BaseCollisionComponent;

	/* static mesh component */
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="PickUpMesh")
	UStaticMeshComponent* DepositBaseMesh;




	// Function to update the text display
	UFUNCTION(BlueprintCallable, Category="MyFunctions")
	void UpdateTextDisplay();

	/** called when something enters the sphere component */
	UFUNCTION()
	virtual void OnOverlapBegin(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	/** called when something leaves the sphere component */
	UFUNCTION()
	virtual void OnOverlapEnd(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;



	// depositBase an item
	UFUNCTION(BlueprintNativeEvent,Category="DepositBaseFunctions")
	bool DepositCurrentItem();

};
