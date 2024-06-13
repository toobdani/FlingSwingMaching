// Fill out your copyright notice in the Description page of Project Settings.

#include "DestroyBullet.h"
#include "Components/BoxComponent.h"


// Sets default values
ADestroyBullet::ADestroyBullet()
{
	//This bullet only exists to be collided by bullets.
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));

	CollisionCollider->SetCollisionProfileName("OverlapAll");

	RootComponent = CollisionCollider;
}

// Called when the game starts or when spawned
void ADestroyBullet::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ADestroyBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

