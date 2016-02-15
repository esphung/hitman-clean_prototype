// Fill out your copyright notice in the Description page of Project Settings.

#include "TopDown_HitmanClean.h"
#include "DepositBase.h"


// Sets default values
ADepositBase::ADepositBase(){
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	bCanBeDamaged = false;
	SetActorEnableCollision(true);// may turn off if causes bugs

	my_name_string = "Deposit Name";
	current_text_string = "";
	clear_text_string = "";
	interaction_text_string = "Interaction";
	find_item_text_string = "Find Item";
	is_found_by_player = false;
	is_deposit_full = false;
	deposit_full_text_string = "Full!";

	my_current_items_value = 0;
	my_maximum_items_value = 2;

	// create the root sphere component
	BaseCollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("BaseSphereComponent"));
	BaseCollisionComponent->InitSphereRadius(150.0f);


	BaseCollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ADepositBase::OnOverlapBegin);       // set up a notification for when this component overlaps something
	BaseCollisionComponent->OnComponentEndOverlap.AddDynamic(this, &ADepositBase::OnOverlapEnd);       // set up a notification for when this component overlaps something

	// set sphere component as root component
	RootComponent = BaseCollisionComponent;

	// create static mesh component
	DepositBaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DepositBaseMesh"));

	// turn physics on for static mesh
	//DepositBaseMesh->SetSimulatePhysics(true);
	DepositBaseMesh->SetSimulatePhysics(false);


	// attach static mesh comp to root comp
	DepositBaseMesh->AttachTo(RootComponent);

	// create text renderer
	VisibleDepositBaseText = CreateDefaultSubobject<UTextRenderComponent>(
		TEXT("DepositBaseText"));
	VisibleDepositBaseText->SetHorizontalAlignment(EHTA_Center);
	VisibleDepositBaseText->SetWorldSize(100.0f);
	VisibleDepositBaseText->SetVisibility(true);// temporary until function built
	VisibleDepositBaseText->RelativeLocation.Z = 150;

	VisibleDepositBaseText->AttachTo(RootComponent);






}// end constructor definition

// Called when the game starts or when spawned
void ADepositBase::BeginPlay(){
	Super::BeginPlay();
	UpdateTextDisplay();

}

// Called every frame
void ADepositBase::Tick( float DeltaTime ){
	Super::Tick( DeltaTime );

}


void ADepositBase::UpdateTextDisplay(){
	VisibleDepositBaseText->SetText(current_text_string);
	/*UE_LOG(YourLog,Warning,TEXT("CountdownTime is %d"), CountdownTime);*/

}

void ADepositBase::OnOverlapBegin(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult){
		// OtherActor is the actor that triggered the event. Check that is not ourself
	if( (OtherActor == nullptr) || (OtherActor == this) || (OtherComp == nullptr) )
		return;

	is_found_by_player = true;

	ATopDown_HitmanCleanCharacter* OtherCharacter = Cast<ATopDown_HitmanCleanCharacter>(OtherActor);

	// CRITICAL SECTION!!!
	if (OtherCharacter->is_holding_item == true){
		// if char has an item
		if (my_current_items_value < my_maximum_items_value){

			if (DepositCurrentItem() == true){
				OtherCharacter->DropCurrentPickUpEvent();
			}
		} else {
			current_text_string = deposit_full_text_string;
			UpdateTextDisplay();
		}
	}

		UpdateTextDisplay();


}// end on overlap begin



void ADepositBase::OnOverlapEnd(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex){
		// OtherActor is the actor that triggered the event. Check that is not ourself
	if( (OtherActor == nullptr) || (OtherActor == this) || (OtherComp == nullptr) )
		return;

	current_text_string = clear_text_string;
	UpdateTextDisplay();


}







bool ADepositBase::DepositCurrentItem_Implementation(){
	if (my_current_items_value < my_maximum_items_value){
		my_current_items_value = my_current_items_value + 1;
		current_text_string = my_name_string + ": " + FString::FromInt(my_current_items_value) + "/" + FString::FromInt(my_maximum_items_value);
		UpdateTextDisplay();
		return true;
	} else {
		return false;
	}


}

