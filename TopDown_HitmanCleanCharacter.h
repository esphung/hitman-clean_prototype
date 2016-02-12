/*
FILENAME:
AUTHOR:				Eric Scott Phung
DATE:					2016.02.10
PURPOSE:
*/
#pragma once
#include "GameFramework/Character.h"
#include "TopDown_HitmanCleanCharacter.generated.h"

UCLASS(Blueprintable)
class ATopDown_HitmanCleanCharacter : public ACharacter{
	GENERATED_BODY()

	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;


public:
	ATopDown_HitmanCleanCharacter();

	// public reference to the player character
	static ATopDown_HitmanCleanCharacter* playerCharacterReference;

	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;



	//Input functions
	void Move_XAxis(float AxisValue);
	void Move_YAxis(float AxisValue);
	void StartGrowing();
	void StopGrowing();

	//Input variables
	FVector CurrentVelocity;
	bool bGrowing;


	// players current stamina amount as a float
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="StaminaVariables")
	float my_current_stamina_value;

	// players maximum stamina amout as a float
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="StaminaVariables")
	float my_maximum_stamina_value;

	// players stamina as a decimal less than 1.0 for percentage value
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="StaminaVariables")
	float my_stamina_percentage;


	// did another actor spot player
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="LogicVariables")
	bool is_seen_by_actor;

	// idi another actor hear player
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="LogicVariables")
	bool is_heard_by_actor;

	// did another catch the player
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="LogicVariables")
	bool is_caught_by_actor;

	// is the player near an interactable item
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="LogicVariables")
	bool is_near_item;

	// is the player sprinting
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="LogicVariables")
	bool is_sprinting;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="HealthVariables")
	float my_current_health_value;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="HealthVariables")
	float my_maximum_health_value;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="HealthVariables")
	float my_health_percentage;


	// event called when debug button is pressed
	UFUNCTION(BlueprintCallable, Category="CustomFunctions")
	void debugBtnPressed();


	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;


	// third person input for development and debugging
	protected:

		/** Called for forwards/backward input */
		void MoveForward(float Value);

		/** Called for side to side input */
		void MoveRight(float Value);

		/**
		 * Called via input to turn at a given rate.
		 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
		 */
		void TurnAtRate(float Rate);

		/**
		 * Called via input to turn look up/down at a given rate.
		 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
		 */
		void LookUpAtRate(float Rate);

		/** Handler for when a touch input begins. */
		void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

		/** Handler for when a touch input stops. */
		void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);


};