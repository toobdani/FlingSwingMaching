// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class FLINGSWINGWING_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Input)
	float TurnRateGamepad;

	//This bool is set to true when the player holds shift
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		bool ChargeMovement;	

	//This float increases as long as the shift button is held. 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float ChargeCount;	

	//This int stores the distance the player moves when they've charged there movement, the distance increases depending on how high the charge count has increased.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int Distance;

	//This bool increases depending on the distance the player is traveling and is checked by other scripts
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int Charge;

	//This is a Timer Handle for the pauses the game has.
	UPROPERTY()
	FTimerHandle FTH;

	//This is the delegate for the timer
	FTimerDelegate FTD;

	//This contains the location of the player's current checkpoint. It can be set in other scripts.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FVector checkpoint;



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

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


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//This is used to update the scripts bools
	UFUNCTION()
	void UpdateValue(bool& value);

	//This function is called to cool down the charge.
	UFUNCTION()
	void Cooldown();	
};
