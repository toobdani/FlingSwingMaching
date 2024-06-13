// Fill out your copyright notice in the Description page of Project Settings.


#include "DestroyableObject.h"
#include "Components/BoxComponent.h"
#include "Engine/World.h"
#include "PlayerCharacter.h"


// Sets default values
ADestroyableObject::ADestroyableObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Initialises collision and mesh, and attachs them together. 
	CollisionCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));

	ObjectMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("mesh"));
	
	CollisionCollider->SetCollisionProfileName("Trigger");

	RootComponent = CollisionCollider;

	ObjectMesh->AttachToComponent(CollisionCollider, FAttachmentTransformRules::KeepRelativeTransform);

	//Sets up a connection between CollisionCollider and OnOverlapBegin.
	CollisionCollider->OnComponentBeginOverlap.AddDynamic(this, &ADestroyableObject::OnOverlapBegin);

}

// Called when the game starts or when spawned
void ADestroyableObject::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ADestroyableObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADestroyableObject::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{	
	//Checks to see if the overlaping actor is the player character
    APlayerCharacter* Character = Cast<APlayerCharacter>(OtherActor);

	//This first checks if the overlapping actor is the player character.
	//Then the code checks to see if the player character's charge is larger then the BreakCount int, if so then this object is destroyed.
    if (Character) 
    {
		if(Character->Charge >= BreakCount)
		{
			Destroy();
		}
   }
}

