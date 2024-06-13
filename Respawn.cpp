// Fill out your copyright notice in the Description page of Project Settings.


#include "Respawn.h"
#include "Components/BoxComponent.h"
#include "Engine/World.h"
#include "PlayerCharacter.h"

// Sets default values
ARespawn::ARespawn()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PrimaryActorTick.bCanEverTick = true;
	//Initialises collision and mesh, and attachs them together. 
	CollisionCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));

	ObjectMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("mesh"));

	CollisionCollider->SetCollisionProfileName("Trigger");

	RootComponent = CollisionCollider;

	ObjectMesh->AttachToComponent(CollisionCollider, FAttachmentTransformRules::KeepRelativeTransform);

	//Sets up a connection between CollisionCollider and OnOverlapBegin.
	CollisionCollider->OnComponentBeginOverlap.AddDynamic(this, &ARespawn::OnOverlapBegin);

}
// Called when the game starts or when spawned
void ARespawn::BeginPlay()
{
	Super::BeginPlay();
	
}
// Called every frame
void ARespawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void ARespawn::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//Checks to see if the overlaping actor is the player character
	APlayerCharacter* Character = Cast<APlayerCharacter>(OtherActor);

	//If the overlapping character is the player character, then a switch statement is called, checking whether the SpawnorSave bool is true or false.
	if (Character)
	{
		switch (SpawnorSave)
		{
		case true:
		{
			//if SpawnorSave is true then the playercharacter script's checkpoint vector is replaced by the script's instance's Checkpoint vector.
			Character->checkpoint = Checkpoint;
		}
		break;
		
		case false:
		{
			//if SpawnorSvae is false then the player character gets moved back to their checkpoint location.
			Character->SetActorLocation(Character->checkpoint);
		}
		break;
		}
	}
}

