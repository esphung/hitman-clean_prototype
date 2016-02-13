// Fill out your copyright notice in the Description page of Project Settings.

#include "TopDown_HitmanClean.h"
#include "MyPickup.h"


// Sets default values
AMyPickup::AMyPickup(){
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Create the root CapsuleComponent to handle the pickup's collision
	BaseCollisionComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("BaseCapsuleComponent"));

	// Set the SphereComponent as the root component.
	RootComponent = BaseCollisionComponent;

	//Create the static mesh component
	PickupMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PickupMesh"));

	// Start with physics simulation disabled, for easy manipulation on UE4 Editor.
	PickupMesh->SetSimulatePhysics(false);


	// Attach the StaticMeshComponent to the RootComponent.
	PickupMesh->AttachTo(RootComponent);

	// Enable the generation of overlapping events and assign a function to be run when it happens.
	BaseCollisionComponent->bGenerateOverlapEvents = true;
	BaseCollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AMyPickup::OnOverlapBegin);

	// Disable Overlap Events on the Mesh
	PickupMesh->bGenerateOverlapEvents = true;


	// set default values for text render
	InGameText = CreateDefaultSubobject<UTextRenderComponent>(
		TEXT("InGameText"));
	InGameText->SetHorizontalAlignment(EHTA_Center);
	InGameText->SetWorldSize(150.0f);
	InGameText->AttachTo(RootComponent);

}// end constructor definiton


void AMyPickup::OnOverlapBegin(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult){
		// OtherActor is the actor that triggered the event. Check that is not ourself
	if( (OtherActor == nullptr) || (OtherActor == this) || (OtherComp == nullptr) )
		return;


	FString SuccessfulPickUpString = "Found Me";
	InGameText->SetText(SuccessfulPickUpString);

	UE_LOG(YourLog,Warning,TEXT("Item picked up by %s"), *OtherActor->GetName());
}