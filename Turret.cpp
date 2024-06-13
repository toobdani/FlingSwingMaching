// Fill out your copyright notice in the Description page of Project Settings.


#include "Turret.h"
#include "Bullet.h"


void ATurret::ShootBullet()
{
	
	//Checks to see if CanSpawn is false
	if (CanSpawn == false)
	{
		//This function starts by creating new varibles that contain the location and rotation of the Spawn variable
		auto SpawnLocation = Spawn->GetActorLocation();
		auto SpawnRotation = Spawn->GetActorRotation();
		//These then create a bullet instance under the SpawnBullet name.
		auto SpawnBullet = GetWorld()->SpawnActor<AActor>(Bullets, SpawnLocation, SpawnRotation);

		//The code then calls the instance created as SpawnBullet so that the bullets values can be edited.
		ABullet* BulletInstance = Cast<ABullet>(SpawnBullet);
		//First it edits the bullets direction and speed by calling the intances SetDirection() function
		BulletInstance->SetDirection(Direction, speedmodifier);

		//It then changes the material of the bullet
		BulletInstance->ObjectMesh->SetMaterial(0, BulletMaterial);

		//After changing these elements the value of BulletInstance is set to null.
		BulletInstance = NULL;
	}
}

