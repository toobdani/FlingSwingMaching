// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"
#include "Components/BoxComponent.h"
#include "Engine/World.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Initialises collision and mesh, and attachs them together. 
	CollisionCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));

	ObjectMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("mesh"));

	RootComponent = CollisionCollider;

	ObjectMesh->AttachToComponent(CollisionCollider, FAttachmentTransformRules::KeepRelativeTransform);


}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	//Sets the Start Vector's values to be the player's starting position
	Start = GetActorLocation();
	
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//If the Movebool is true, then the platform begins movement.
	if (Movebool == true)
	{
		MovePlatform(DeltaTime);
	}

}

void AMovingPlatform::MovePlatform(float DeltaTime)
{
	//This starts by checking if BeginMoving is true.
	if (BeginMoving == true)
	{
		//Every frame the FVector CurrentLocation is set to the platforms current position.
		FVector CurrentLocation = GetActorLocation();

		//As long as the StopMove bool is false, the platforms location will increase each frame.
		if (StopMove == false)
		{
			CurrentLocation = CurrentLocation + (PlatformVelocity * DeltaTime);
		}

		//The DistanceMoved float is made and set to the distance that the platform has currently moved.
		float DistanceMoved = FVector::Dist(Start, CurrentLocation);


		//This if statement call the TurnBack() function, to see if it returned as true.
		if (TurnBack())
		{
			//if TurnBack() returns true, the code then checks to see if the Pause bool is true
			if (Pause == true)
			{
				//If Pause is true, then the delay function is called.
				Delay(DeltaTime);
			}
			else
			{
				//if there is no pause, then the platform instantly begins moving the opposite way.
				PlatformVelocity = -PlatformVelocity;
				Start = GetActorLocation();
			}
		}

		//This sets the platforms position to be CurrentLocation, moving the platform.
		SetActorLocation(CurrentLocation);
	}

}

bool AMovingPlatform::TurnBack() const
{
	//This sets the TurnBack bool as true if the value of the GetDistanceMoved bool is greated then the value of MoveDistance
	return GetDistanceMoved() > MoveDistance;
}

float AMovingPlatform::GetDistanceMoved() const
{
	//This returns the value of the distance between the players location and the Start vector
	return FVector::Dist(Start, GetActorLocation());
}

void AMovingPlatform::Delay(float DeltaTime)
{
	//This function pauses movement by setting the StopMove bool as true.
	StopMove = true;

	//It adds to the DelayTime float each time the function is called
	DelayTime += DeltaTime;

	//This function checks whether the DelayTime float is greater or equal to the wait float.
	if (DelayTime >= wait)
	{
		//If that is the case, then the platform begins moving backwards and the DelayTime value returns to 0.
		PlatformVelocity = -PlatformVelocity;
		Start = GetActorLocation();
		DelayTime = 0.f;
		StopMove = false;
	}
}


