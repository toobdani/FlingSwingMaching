// Fill out your copyright notice in the Description page of Project Settings.


#include "Bomb.h"
#include "Components/SphereComponent.h"
#include "Engine/World.h"
#include "PlayerCharacter.h"

// Sets default values
ABomb::ABomb()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//This starts by initialising the sphere collision and mesh, setting the sphere size and setting as root component
	CollisionCollider = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));

	CollisionCollider->SetSphereRadius(100);

	CollisionCollider->SetCollisionProfileName("Trigger");

	RootComponent = CollisionCollider;

	ObjectMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Bomb Mesh"));

	//The code sets the ObjectMesh to be the sphere mesh
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereMeshAsset(TEXT("/Engine/BasicShapes/Sphere"));
	if (SphereMeshAsset.Succeeded())
	{
		ObjectMesh->SetStaticMesh(SphereMeshAsset.Object);
	}

	ObjectMesh->SetupAttachment(CollisionCollider);

	//This binds the CollisionCollider to OnOverlapBegin() and OnOverlapEnd()
	CollisionCollider->OnComponentBeginOverlap.AddDynamic(this, &ABomb::OnOverlapBegin);

	CollisionCollider->OnComponentEndOverlap.AddDynamic(this, &ABomb::OnOverlapEnd);


}

// Called when the game starts or when spawned
void ABomb::BeginPlay()
{
	Super::BeginPlay();

	//This Sets StartsBlowingUp as true
	StartBlowingUp = true;
	
}

// Called every frame
void ABomb::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//This will trigger the timer is StartBlowingUp is true, before setting StartBlowingUp as false
	if(StartBlowingUp == true)
	{
		StartBlowingUp = false;
		GetGameInstance()->TimerManager->SetTimer(TimerHandle, this, &ABomb::BlowUp, BlowUpTime, true);
	}
}

void ABomb::BlowUp()
{
	//If the playercharacter script has been assigned to the MyChild variable then this code will happen.
	if(MyChild != nullptr)
	{
		//If the player is in the collision during the point of explosion they will respawn at checkpoint.
		if(DangerZone == true)
		{
			MyChild->SetActorLocation(MyChild->checkpoint);
		}
	}
	//The blownup bool is set to true so that the bombspawn can remove the instance of the bomb
	blownup = true;
	//this destroys the instance of the bomb
	Destroy();
}

void ABomb::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//This checks if it is colliding with the player
    APlayerCharacter* Character = Cast<APlayerCharacter>(OtherActor);
    if (Character) 
    {
		//If the player has entered the collision then DangerZone is set to true, and the character is stored in the MyChild variable
		DangerZone = true;
		MyChild = Character;
   	}
}

void ABomb::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

	//This checks if the player character has exited the collision, and if so DangerZone is set to false.
	APlayerCharacter* Character = Cast<APlayerCharacter>(OtherActor);
    if (Character) 
	{
		DangerZone = false;
	}
}

