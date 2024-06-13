// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet.h"
#include "Components/BoxComponent.h"
#include "Engine/World.h"
#include "PlayerCharacter.h"
#include "DestroyBullet.h"

// Sets default values
ABullet::ABullet()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	//The script begins by initialsing the box component and meshes.
	CollisionCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));

	//The code sets the size of CollisionCollider and sets it to a trigger
	CollisionCollider->SetBoxExtent(FVector(40, 40, 40));

	CollisionCollider->SetCollisionProfileName("Trigger");

	//This sets CollisionCollider as the Root Component and attatches the meshes to it.
	RootComponent = CollisionCollider;

	ObjectMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Bullet Mesh"));

	//This section finds the Sphere mesh from the file path and attaches it to the ObjectMesh
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereMeshAsset(TEXT("/Engine/BasicShapes/Sphere"));
	if (SphereMeshAsset.Succeeded())
	{
		ObjectMesh->SetStaticMesh(SphereMeshAsset.Object);
	}

	ObjectMesh->SetupAttachment(CollisionCollider);

	//This sets the scale of the bullet to the ObjectSize
	SetActorRelativeScale3D(ObjectSize);

	//Sets up a connection between CollisionCollider and OnOverlapBegin.
	CollisionCollider->OnComponentBeginOverlap.AddDynamic(this, &ABullet::OnOverlapBegin);


}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();

	//On BeginPlay() SetDirection is called if BulletVelocity's value is 0
	if (BulletVelocity == FVector(0))
	{
		SetDirection(Direction, SpeedModifier);
	}
}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//This calls the Moving Function every tick.
	Moving(DeltaTime);
}

void ABullet::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//Checks to see if the overlaping actor is the player character
	APlayerCharacter* Character = Cast<APlayerCharacter>(OtherActor);
	if (Character)
	{
		//If it is the player character then the code causes the player to go back to checkpoint and destroys the bullet instance.
		Character->SetActorLocation(Character->checkpoint);
		Destroy();
	}

	//Checks to see if the overlaping actor is a DestroyBullet script
	ADestroyBullet* DB = Cast<ADestroyBullet>(OtherActor);
	if (DB)
	{
		//if so then the instance of the bullet is destroyed.
		Destroy();
	}
}

void ABullet::Moving(float DeltaTime)
{
	//Every frame the code gets the current location and adds to it by the bullet velocity.
	FVector CurrentLocation = GetActorLocation();
	CurrentLocation = CurrentLocation + (BulletVelocity * DeltaTime);
	SetActorLocation(CurrentLocation);
}


void ABullet::SetDirection(int GoDirection, float SModifier)
{
	//This function uses a switch statement that checks the value of GoDirection
	switch (GoDirection)
	{
	case 0:
	{
		//Down
		BulletVelocity = FVector((100 * SModifier), 0, 0);
	}
	break;
	case 1:
	{
		//Left
		BulletVelocity = FVector(0, (100 * SModifier), 0);
	}
	break;
	case 2:
	{
		//Right
		BulletVelocity = FVector(0, (-100 * SModifier), 0);
	}
	break;
	case 3:
	{
		//Up
		BulletVelocity = FVector((-100 * SModifier), 0, 0);
	}
	break;
	}

}


