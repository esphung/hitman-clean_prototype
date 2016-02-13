// Fill out your copyright notice in the Description page of Project Settings.

#include "TopDown_HitmanClean.h"
#include "Deposit.h"


// Sets default values
ADeposit::ADeposit(){
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	bCanBeDamaged = false;
	SetActorEnableCollision(true);// may turn off if causes bugs

	my_name_string = "Deposit";
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


	BaseCollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ADeposit::OnOverlapBegin);       // set up a notification for when this component overlaps something
	BaseCollisionComponent->OnComponentEndOverlap.AddDynamic(this, &ADeposit::OnOverlapEnd);       // set up a notification for when this component overlaps something

	// set sphere component as root component
	RootComponent = BaseCollisionComponent;

	// create static mesh component
	DepositMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DepositMesh"));

	// turn physics on for static mesh
	//DepositMesh->SetSimulatePhysics(true);
	DepositMesh->SetSimulatePhysics(false);


	// attach static mesh comp to root comp
	DepositMesh->AttachTo(RootComponent);

	// create text renderer
	VisibleDepositText = CreateDefaultSubobject<UTextRenderComponent>(
		TEXT("DepositText"));
	VisibleDepositText->SetHorizontalAlignment(EHTA_Center);
	VisibleDepositText->SetWorldSize(150.0f);
	VisibleDepositText->SetVisibility(true);// temporary until function built
	VisibleDepositText->RelativeLocation.Z = 150;

	VisibleDepositText->AttachTo(RootComponent);






}// end constructor definition

// Called when the game starts or when spawned
void ADeposit::BeginPlay(){
	Super::BeginPlay();
	UpdateTextDisplay();

}

// Called every frame
void ADeposit::Tick( float DeltaTime ){
	Super::Tick( DeltaTime );

}


void ADeposit::UpdateTextDisplay(){
	VisibleDepositText->SetText(current_text_string);
	/*UE_LOG(YourLog,Warning,TEXT("CountdownTime is %d"), CountdownTime);*/

}

void ADeposit::OnOverlapBegin(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult){
		// OtherActor is the actor that triggered the event. Check that is not ourself
	if( (OtherActor == nullptr) || (OtherActor == this) || (OtherComp == nullptr) )
		return;


	// check the deposit
	UpdateTextDisplay();
	CheckDeposit();
	//DepositCurrentItem();

}



void ADeposit::OnOverlapEnd(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex){
		// OtherActor is the actor that triggered the event. Check that is not ourself
	if( (OtherActor == nullptr) || (OtherActor == this) || (OtherComp == nullptr) )
		return;


	current_text_string = clear_text_string;
	UpdateTextDisplay();


}




bool ADeposit::CheckDeposit_Implementation(){
	if (my_current_items_value >= my_maximum_items_value){
		is_deposit_full = true;
		current_text_string = my_name_string + ": " + deposit_full_text_string;
		UpdateTextDisplay();
		return true;
	} else {
		current_text_string = my_name_string;
		UpdateTextDisplay();
		return false;
	}
	return false;
}




void ADeposit::DepositCurrentItem_Implementation(){
	if (CheckDeposit() != true){
		/* code */
		my_current_items_value++;
		current_text_string = my_name_string + ": " + FString::FromInt(my_current_items_value) + "/" + FString::FromInt(my_maximum_items_value);
		UpdateTextDisplay();
	}
}


