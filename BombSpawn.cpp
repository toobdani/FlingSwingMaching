// Fill out your copyright notice in the Description page of Project Settings.


#include "BombSpawn.h"
#include "Components/SphereComponent.h"
#include "Engine/World.h"
#include "Bomb.h"
#include "PlayerCharacter.h"

// Sets default values
ABombSpawn::ABombSpawn()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//This initializes the CollisionCollider and binds it to the OnOverlapBegin() function.
	CollisionCollider = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));

	CollisionCollider->SetCollisionProfileName("Trigger");
	
	RootComponent = CollisionCollider;

	CollisionCollider->OnComponentBeginOverlap.AddDynamic(this, &ABombSpawn::OnOverlapBegin);
}

// Called when the game starts or when spawned
void ABombSpawn::BeginPlay()
{
	Super::BeginPlay();

	//At start CanSpawn is set to true.
	CanSpawn = true;
	
}
// Called every frame
void ABombSpawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	//If the InstanceBomb variable is not null, then it will be set to null when its contained bomb's blownup bool is set to true.
	if(InstanceBomb != nullptr)
	{
		if(InstanceBomb->blownup == true)
		{
			InstanceBomb = nullptr;
		}
	}

}
void ABombSpawn::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//If the player character enters the trigger, then a bomb is spawned at the location and rotation of the Spawn
	//This bomb is attatched to the InstanceBomb variable and has its timer set to the value of BombWait.
    APlayerCharacter* Character = Cast<APlayerCharacter>(OtherActor);
    if (Character) 
    {
		if(InstanceBomb == nullptr)
		{
			auto SpawnLocation = Spawn->GetActorLocation();
			auto SpawnRotation = Spawn->GetActorRotation();
			auto SpawnBomb = GetWorld()->SpawnActor<ABomb>(Bomb, SpawnLocation, SpawnRotation);

			InstanceBomb = Cast<ABomb>(SpawnBomb);
			InstanceBomb->BlowUpTime = BombWait;
		}
   	}
}
