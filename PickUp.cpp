// Fill out your copyright notice in the Description page of Project Settings.

#include "TopDown_HitmanClean.h"
#include "PickUp.h"


// Sets default values
APickUp::APickUp(){
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	SetActorEnableCollision(true);

	bCanBeDamaged = false;


	// set a default item name
	ItemNameText = "Generic Item";

	// pick up logic variables
	is_near_player = false;

	// pick up is active when it is created
	isActive = true;

	// create the root sphere component
	BaseCollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("BaseSphereComponent"));
	BaseCollisionComponent->InitSphereRadius(150.0f);


	BaseCollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &APickUp::OnOverlapBegin);       // set up a notification for when this component overlaps something
	BaseCollisionComponent->OnComponentEndOverlap.AddDynamic(this, &APickUp::OnOverlapEnd);       // set up a notification for when this component overlaps something

	// set sphere component as root component
	RootComponent = BaseCollisionComponent;

	// create static mesh component
	PickUpMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PickUpMesh"));

	// turn physics on for static mesh
	//PickUpMesh->SetSimulatePhysics(true);
	PickUpMesh->SetSimulatePhysics(false);


	// attach static mesh comp to root comp
	PickUpMesh->AttachTo(RootComponent);





}// end constructor def







void APickUp::OnOverlapEnd(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex){
		// OtherActor is the actor that triggered the event. Check that is not ourself
	if( (OtherActor == nullptr) || (OtherActor == this) || (OtherComp == nullptr) )
		return;

/*
	// what to do
	is_near_player = false;

	if (is_near_player == false){
		// show bool value
		UE_LOG(YourLog, Warning, TEXT("FALSE"));
		UE_LOG(YourLog,Warning,TEXT("%s is not close enough to this pick up item"), *OtherActor->GetName());
	}
*/
}

void APickUp::PickedUp(){
	/* Has no default behavior when picked up */
	SetActorEnableCollision(false);
	is_near_player = false;
	isActive = false;

}

FString APickUp::GetMyNameString(){
	// return this items name
	return ItemNameText;
}


void APickUp::OnOverlapBegin(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult){
		// OtherActor is the actor that triggered the event. Check that is not ourself
	if( (OtherActor == nullptr) || (OtherActor == this) || (OtherComp == nullptr) )
		return;

/*	// what to do if actor overlaps pick up item
	is_near_player = true;

	// cast to player character with actor reference
	ATopDown_HitmanCleanCharacter* OtherCharacter = Cast<ATopDown_HitmanCleanCharacter>(OtherActor);
	AttachPickUpToPawn(OtherCharacter,"pick_up_001");

	// attach pickup to player character
	if (OtherCharacter->GetHasCurrentItem() != true){
		if (AttachPickUpToPawn(OtherCharacter,"pick_up_001") == true){
			OtherCharacter->EquipCurrentPickUpEvent(this);
		}
	} else {
		return;
	};


	if (is_near_player == true){
		// show bool value
		UE_LOG(YourLog, Warning, TEXT("TRUE"));
		UE_LOG(YourLog,Warning,TEXT("%s is close enough to item to pick it up"), *OtherActor->GetName());
	}*/

}



bool APickUp::AttachPickUpToPawn(APawn* PickUpOwner, FString SkeletalCompName){
	OwningPawn = PickUpOwner; // Sets the owner of this PickUp. (Note: OwningPawn  is a APawn* member in my PickUp class.)
	SetOwner(OwningPawn); // AActor::SetOwner(APawn*);

	// A method i created to get any skeletal component from the owning pawn. (Could be made a template to function to get any type.)
	USkeletalMeshComponent* ArmMesh = GetPawnSkeletalComp(SkeletalCompName);

	if (ArmMesh) // Check to see if our rig Skeletal Mesh Component is good.
	{
	// AActor::AttachRootComponentTo(..)
		AttachRootComponentTo(PickUpMesh, FName(TEXT("pick_up_001")), EAttachLocation::SnapToTarget); // Attach the root component of our PickUp actor to the ArmMesh at the location of the socket.
		return true; // Note: We can only assume it is attached, since epic did not provide a return value.
	}
	else
	{
		return false;
	}
}

USkeletalMeshComponent* APickUp::GetPawnSkeletalComp(FString ComponentName){
	TArray<UActorComponent*> Components; // Array for Pawns components
	USkeletalMeshComponent* ArmMesh = NULL; // Will hold the skeletal mesh we want

	if (OwningPawn)
		OwningPawn->GetComponents(Components); // Get the components from the owning pawn

	for (UActorComponent* Comp : Components)
	{
		ArmMesh = Cast<USkeletalMeshComponent>(Comp); // Cast any component to Skeletal Comp.
		if (ArmMesh) // If we have a skeletal mesh
		{
			if (ArmMesh->GetName() == ComponentName) // Check to see if its the one we want.
				return ArmMesh;
		}
	}

	return NULL; // Finished with out finding the component we wanted.
}




