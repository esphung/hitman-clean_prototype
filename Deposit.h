// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TopDown_HitmanCleanCharacter.h"
#include "PickUp.h"
#include "GameFramework/Actor.h"
#include "Deposit.generated.h"

UCLASS()
class TOPDOWN_HITMANCLEAN_API ADeposit : public AActor{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADeposit();

	// Text to be rendered with deposit
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="TimerVariables")
	UTextRenderComponent* VisibleDepositText;

	// deposit instance's name
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="DepositVariables")
	FString my_name_string;

	// string used to clear out text displayed
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="DepositVariables")
	FString clear_text_string;

	// current text string displayed
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="DepositVariables")
	FString current_text_string;

	// text when interacting with player
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="DepositVariables")
	FString interaction_text_string;

	// text shown when player needs to find an item
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="DepositVariables")
	FString find_item_text_string;

	// text shown when deposit is full
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="DepositVariables")
	FString deposit_full_text_string;

	// logic value when deposit has been found by the player
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="DepositVariables")
	bool is_found_by_player;

	// current amount of items the deposit is holding
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="DepositVariables")
	int32 my_current_items_value;

	// maximum amount of items the deposit can hold
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="DepositVariables")
	int32 my_maximum_items_value;

	// checks if deposit is full
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="DepositVariables")
	bool is_deposit_full;



	/* Simple primitive collision component used as root */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="PickUpCollision")
	USphereComponent* BaseCollisionComponent;

	/* static mesh component */
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="PickUpMesh")
	UStaticMeshComponent* DepositMesh;




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

	// chek if deposit is full
	UFUNCTION(BlueprintNativeEvent,Category="DepositFunctions")
	bool CheckDeposit();

	// deposit an item
	UFUNCTION(BlueprintNativeEvent,Category="DepositFunctions")
	void DepositCurrentItem();

};
