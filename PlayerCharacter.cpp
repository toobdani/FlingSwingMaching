// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rate for input
	TurnRateGamepad = 50.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	//This sets the game's timer.
	FTD = FTimerDelegate::CreateUObject(this, &APlayerCharacter::Cooldown);

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)

}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	//This sets the checkpoint as the players starting location
	checkpoint = GetActorLocation();
	
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//This if statement checks whether the player is holding shift, if so the ChargeMovement bool is set to true and the ChargeCount is increased. 
	//When the player lets go these are set to false and 0 respectively, with Distance and Charge also being set to 0
	if (GetWorld()->GetFirstPlayerController()->IsInputKeyDown(EKeys::LeftShift))
	{
		ChargeMovement = true;
		ChargeCount += 0.05f;
	}

	else
	{
		ChargeMovement = false;
		ChargeCount = 0;
		Distance = 0;
		Charge = 0;
	}

	//This checks whether the ChargeMovement bool is true. If so it then checks the count of ChargeCount, and sets the Distance and Charge variables depending on the amount charged. 
	if (ChargeMovement)
	{
		if (ChargeCount >= 8)
		{
			Distance = 3100;
			Charge = 3;
		}
		else if (ChargeCount >= 5)
		{
			Distance = 2300;
			Charge = 2;
		}
		else if (ChargeCount >= 3)
		{
			Distance = 1600;
			Charge = 1;
		}
		else 
		{
			Distance = 0;

		}
	}
	
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Set up gameplay key bindings
	check(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Move Forward / Backward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("Move Right / Left", this, &APlayerCharacter::MoveRight);

}

void APlayerCharacter::UpdateValue(bool& value)
{
	value = false;
}

//This function is called by the timer inbetween charges, so the player can't constantly charge.
void APlayerCharacter::Cooldown()
{
	
	Charge = 0;
}

void APlayerCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
	Jump();
}

void APlayerCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
	StopJumping();
}

void APlayerCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * TurnRateGamepad * GetWorld()->GetDeltaSeconds());
}

void APlayerCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * TurnRateGamepad * GetWorld()->GetDeltaSeconds());
}
void APlayerCharacter::MoveForward(float Value)
{
	//This switch statement checks to see if Chargemovement is true.
	switch (ChargeMovement)
	{
	case false:
	{
		if ((Controller != nullptr) && (Value != 0.0f))
		{
			// find out which way is forward
			const FRotator Rotation = Controller->GetControlRotation();
			const FRotator YawRotation(0, Rotation.Yaw, 0);

			// get forward vector
			const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
			AddMovementInput(Direction, Value);
		}
	}
	break;
	case true:
	{
		//if ChargeMovement is true then the code checks whether Charge is more then 
		//When both these are true, and the player presses either S or W, then the player will be launched into the given direction, before the game calls the Cooldown.
		if(Charge > 0)
		{
			if (GetWorld()->GetFirstPlayerController()->IsInputKeyDown(EKeys::S))
		{
			LaunchCharacter(FVector(-Distance,0, 0), true, true);
			ChargeCount = 0;
			Distance = 0;
			GetWorld()->GetTimerManager().SetTimer(FTH, FTD, 0.2f, false);
		}
		else if (GetWorld()->GetFirstPlayerController()->IsInputKeyDown(EKeys::W))
		{
			LaunchCharacter(FVector(Distance, 0, 0), true, true);
			ChargeCount = 0;
			Distance = 0;
			GetWorld()->GetTimerManager().SetTimer(FTH, FTD, 0.2f, false);
		}
		}
	}
	break;
	}
}



void APlayerCharacter::MoveRight(float Value)
{
	//This switch statement checks to see if Chargemovement is true.
	switch (ChargeMovement)
	{
	case false:
	{

		if ((Controller != nullptr) && (Value != 0.0f))
		{
			// find out which way is right
			const FRotator Rotation = Controller->GetControlRotation();
			const FRotator YawRotation(0, Rotation.Yaw, 0);

			// get right vector 
			const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
			// add movement in that direction
			AddMovementInput(Direction, Value);
		}
	}
	break;
	case true:
	{
		//if ChargeMovement is true then the code checks whether Charge is more then 
		//When both these are true, and the player presses either S or W, then the player will be launched into the given direction, before the game calls the Cooldown.
		if(Charge > 0)
		{
		if (GetWorld()->GetFirstPlayerController()->IsInputKeyDown(EKeys::A))
		{
			LaunchCharacter(FVector(0, -Distance, 0), true, true);
			ChargeCount = 0;
			Distance = 0;
			GetWorld()->GetTimerManager().SetTimer(FTH, FTD, 0.2f, false);
		}
		else if (GetWorld()->GetFirstPlayerController()->IsInputKeyDown(EKeys::D))
		{
			LaunchCharacter(FVector(0, Distance, 0), true, true);
			ChargeCount = 0;
			Distance = 0;
			GetWorld()->GetTimerManager().SetTimer(FTH, FTD, 0.2f, false);
		}
		}
	}
	break;
	}

}

