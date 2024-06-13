// Fill out your copyright notice in the Description page of Project Settings.


#include "P_Platform_Restart.h"
#include "PlayerPlatform.h"

// Sets default values
AP_Platform_Restart::AP_Platform_Restart()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AP_Platform_Restart::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AP_Platform_Restart::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AP_Platform_Restart::RestartLocation()
{
	//Upon calling this function the Instance Platform's location is set to StartLocation
	 InstancePlatform->SetActorLocation(StartLocation);
}

