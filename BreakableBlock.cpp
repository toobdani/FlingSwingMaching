// Fill out your copyright notice in the Description page of Project Settings.


#include "BreakableBlock.h"
#include "Components/BoxComponent.h"
#include "Engine/World.h"
#include "PlayerCharacter.h"

// Sets default values
ABreakableBlock::ABreakableBlock()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//The code starts by initializing the colliders and mesh, binding the overlap events to TriggerCollider.
	CollisionCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));

	TriggerCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerC"));

	ObjectMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("mesh"));

	TriggerCollider->SetCollisionProfileName("Trigger");

	RootComponent = CollisionCollider;

	ObjectMesh->AttachToComponent(CollisionCollider, FAttachmentTransformRules::KeepRelativeTransform);

	
	TriggerCollider->AttachToComponent(CollisionCollider, FAttachmentTransformRules::KeepRelativeTransform);

	TriggerCollider->OnComponentBeginOverlap.AddDynamic(this, &ABreakableBlock::OnOverlapBegin);

}
// Called when the game starts or when spawned
void ABreakableBlock::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABreakableBlock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

void ABreakableBlock::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//This checks whether the player is the one to enter the trigger
    APlayerCharacter* Character = Cast<APlayerCharacter>(OtherActor);
    if (Character) 
    {
		//If Triggered is false then the DeactivateBlock() function is called via a timer. 
		if (Triggered == false)
		{
			Triggered = true;
			GetGameInstance()->TimerManager->SetTimer(TimerHandle, this, &ABreakableBlock::DeactivateBlock, BreakSpeed, true);
		}
   	}
}
void ABreakableBlock::DeactivateBlock()
{
	//The DeactivateBlock() function sets the Hidden bool as true and hides the actor, it also changes the collision type of the collision
	Hidden = true;
	SetActorHiddenInGame(true);
	ObjectMesh->SetCollisionProfileName("OverlapAllDynamic");
	//After this it sets a timer of 5 seconds to reactivate.
	GetGameInstance()->TimerManager->SetTimer(TimerHandle, this, &ABreakableBlock::ReactivateBlock, 5, true);
}

void ABreakableBlock::ReactivateBlock()
{
	//In ReactivateBlock() the Triggered and Hidden bool are set to false and the block reappears. 
	Triggered = false;
	Hidden = false;
	SetActorHiddenInGame(false);
	ObjectMesh->SetCollisionProfileName("BlockAllDynamic");
}

