/*
FILENAME:
AUTHOR:				Eric Scott Phung
DATE:					2016.02.10
PURPOSE:
*/

#include "TopDown_HitmanClean.h"
#include "TopDown_HitmanCleanCharacter.h"

ATopDown_HitmanCleanCharacter::ATopDown_HitmanCleanCharacter(){
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// instance stamina variables
	my_current_stamina_value =		100.0;
	my_maximum_stamina_value =		100.0;
	my_stamina_percentage =	(my_current_stamina_value/my_maximum_stamina_value);
	// instance logic variables
	is_seen_by_actor = 		false;
	is_heard_by_actor = 	false;
	is_caught_by_actor = 	false;
	is_near_item =				false;
	is_sprinting =				false;

	// instance health variables
	my_current_health_value =			100.0;
	my_maximum_health_value =			100.0;
	my_health_percentage = (my_current_health_value/my_maximum_health_value);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->AttachTo(RootComponent);
	CameraBoom->bAbsoluteRotation = true; // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->RelativeRotation = FRotator(-60.f, 0.f, 0.f);
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->AttachTo(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm


	// get reference to player's controlled character
	/*ATopDown_HitmanCleanCharacter* playerCharacterReference;
	UCameraComponent* PlayerCameraRef;*/





	UE_LOG(YourLog,Warning,TEXT("Player Character object was cconstructed."));
}// end null constructor definition

// debug button event
void ATopDown_HitmanCleanCharacter::debugBtnPressed(){
	UE_LOG(YourLog,Warning,TEXT("DEBUG BTN PRESSED!"));
}


void ATopDown_HitmanCleanCharacter::Move_XAxis(float AxisValue){
	// Move at 100 units per second forward or backward
	CurrentVelocity.X = FMath::Clamp(AxisValue, -1.0f, 1.0f) * 100.0f;
}

void ATopDown_HitmanCleanCharacter::Move_YAxis(float AxisValue){
	// Move at 100 units per second right or left
	CurrentVelocity.Y = FMath::Clamp(AxisValue, -1.0f, 1.0f) * 100.0f;
}

void ATopDown_HitmanCleanCharacter::StartGrowing(){
	bGrowing = true;
}

void ATopDown_HitmanCleanCharacter::StopGrowing(){
	bGrowing = false;
}




// Called when the game starts or when spawned
void ATopDown_HitmanCleanCharacter::BeginPlay(){
	Super::BeginPlay();
}

// Called every frame
void ATopDown_HitmanCleanCharacter::Tick( float DeltaTime ){
	Super::Tick( DeltaTime );
	// Handle growing and shrinking based on our "Grow" action
	{
		float CurrentScale = GetCapsuleComponent()->GetComponentScale().X;
		if (bGrowing){
		// Grow to double size over the course of one second
			CurrentScale += DeltaTime;
		} else{
		// Shrink half as fast as we grow
			CurrentScale -= (DeltaTime * 0.5f);
		}
		// Make sure we never drop below our starting size, or increase past double size.
		CurrentScale = FMath::Clamp(CurrentScale, 1.0f, 2.0f);
		GetCapsuleComponent()->SetWorldScale3D(FVector(CurrentScale));
	}

	// Handle movement based on our "MoveX" and "MoveY" axes
	{
		if (!CurrentVelocity.IsZero()){
			FVector NewLocation = GetActorLocation() + (CurrentVelocity * DeltaTime);
			SetActorLocation(NewLocation);
		}
	}
}

// Called to bind functionality to input
void ATopDown_HitmanCleanCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent){
	Super::SetupPlayerInputComponent(InputComponent);

	// Respond when our "Grow" key is pressed or released.
	InputComponent->BindAction("Grow", IE_Pressed, this, &ATopDown_HitmanCleanCharacter::StartGrowing);
	InputComponent->BindAction("Grow", IE_Released, this, &ATopDown_HitmanCleanCharacter::StopGrowing);

	// Respond every frame to the values of our two movement axes, "MoveX" and "MoveY".
	InputComponent->BindAxis("MoveX", this, &ATopDown_HitmanCleanCharacter::Move_XAxis);
	InputComponent->BindAxis("MoveY", this, &ATopDown_HitmanCleanCharacter::Move_YAxis);

	InputComponent->BindAxis("MoveForward", this, &ATopDown_HitmanCleanCharacter::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &ATopDown_HitmanCleanCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	InputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	InputComponent->BindAxis("TurnRate", this, &ATopDown_HitmanCleanCharacter::TurnAtRate);
	InputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	InputComponent->BindAxis("LookUpRate", this, &ATopDown_HitmanCleanCharacter::LookUpAtRate);

	// handle touch devices
	InputComponent->BindTouch(IE_Pressed, this, &ATopDown_HitmanCleanCharacter::TouchStarted);
	InputComponent->BindTouch(IE_Released, this, &ATopDown_HitmanCleanCharacter::TouchStopped);

	// handle debug btn input
	InputComponent->BindAction("DebugBtn", IE_Released, this, &ATopDown_HitmanCleanCharacter::debugBtnPressed);
}


void ATopDown_HitmanCleanCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location){
	// jump, but only on the first touch
	if (FingerIndex == ETouchIndex::Touch1)
	{
		Jump();
	}
}

void ATopDown_HitmanCleanCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location){
	if (FingerIndex == ETouchIndex::Touch1)
	{
		StopJumping();
	}
}

void ATopDown_HitmanCleanCharacter::TurnAtRate(float Rate){
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ATopDown_HitmanCleanCharacter::LookUpAtRate(float Rate){
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void ATopDown_HitmanCleanCharacter::MoveForward(float Value){
	if ((Controller != NULL) && (Value != 0.0f)){
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void ATopDown_HitmanCleanCharacter::MoveRight(float Value){
	if ( (Controller != NULL) && (Value != 0.0f) ){
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}


