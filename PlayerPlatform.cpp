// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPlatform.h"
#include "Components/BoxComponent.h"
#include "Engine/World.h"
#include "PlayerCharacter.h"

// Sets default values
APlayerPlatform::APlayerPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Initialises collision and mesh, and attachs them together.
	CollisionCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));

	TriggerCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerC"));

	ObjectMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("mesh"));

	TriggerCollider->SetCollisionProfileName("Trigger");

	RootComponent = CollisionCollider;

	ObjectMesh->AttachToComponent(CollisionCollider, FAttachmentTransformRules::KeepRelativeTransform);

	
	TriggerCollider->AttachToComponent(CollisionCollider, FAttachmentTransformRules::KeepRelativeTransform);

	//Binds TriggerCollider to OnOverlapBegin() and OnOverlapEnd()
	TriggerCollider->OnComponentBeginOverlap.AddDynamic(this, &APlayerPlatform::OnOverlapBegin);

	TriggerCollider->OnComponentEndOverlap.AddDynamic(this, &APlayerPlatform::OnOverlapEnd);

	//Sets BeginMoving as false
	BeginMoving = false;
	Movebool = true;

}


// Called when the game starts or when spawned
void APlayerPlatform::BeginPlay()
{
	Super::BeginPlay();
	//Sets the Start Vector's values to be the player's starting position
	Start = GetActorLocation();
}

// Called every frame
void APlayerPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//If the Movebool is true, then the platform begins movement.
	if (Movebool == true)
	{
		MovePlatform(DeltaTime);
	}

}

void APlayerPlatform::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//Checks to see if the overlaping actor is the player character
    APlayerCharacter* Character = Cast<APlayerCharacter>(OtherActor);
    if (Character) 
    {
		//if the player enters the trigger, BeginMoving is set to true and the platform begins moving.
		BeginMoving = true;
   	}
}

void APlayerPlatform::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

	//Checks to see if the overlaping actor is the player character
    APlayerCharacter* Character = Cast<APlayerCharacter>(OtherActor);
    if (Character) 
	{
		//If the player exits the trigger then BeginMoving is set to false and the platform stops moving.
		BeginMoving = false;
		//Then the platforms location returns back to the value set in start.
		SetActorLocation(Start);
	}

}

void APlayerPlatform::MovePlatform(float DeltaTime)
{
	//This starts by checking if BeginMoving is true.
	if (BeginMoving == true)
	{
		//Every frame the FVector CurrentLocation is set to the platforms current position.
		FVector CurrentLocation = GetActorLocation();


		//Changes the value of CurrentLocation slightly so the platforms location will increase each frame.
		CurrentLocation = CurrentLocation + (PlatformVelocity * DeltaTime);

		//The DistanceMoved float is made and set to the distance that the platform has currently moved.
		float DistanceMoved = FVector::Dist(Start, CurrentLocation);

		//This if statement call the TurnBack() function, to see if it returned as true.
		if (TurnBack())
		{
			//the platform gets set to move the other way, before setting BeforeMoving as false.
			PlatformVelocity = -PlatformVelocity;
			Start = GetActorLocation();
			BeginMoving = false;
		}

		//This sets the platforms position to be CurrentLocation, moving the platform.
		SetActorLocation(CurrentLocation);
	}

}

bool APlayerPlatform::TurnBack() const
{
	//This sets the TurnBack bool as true if the value of the GetDistanceMoved bool is greated then the value of MoveDistance
	return GetDistanceMoved() > MoveDistance;
}

float APlayerPlatform::GetDistanceMoved() const
{
	//This returns the value of the distance between the players location and the Start vector
	return FVector::Dist(Start, GetActorLocation());
}

