// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TargetPoint.h"
#include "DestroyableObject.h"
#include "Turret.generated.h"

/**
 * 
 */
UCLASS()
class FLINGSWINGWING_API ATurret : public ADestroyableObject
{
	GENERATED_BODY()

public:

	//This allows me to attatch a target point from the scene to my code
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		ATargetPoint* Spawn;

	//This allows me to attatch the Bullet script to my code so that they can be spawned.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<AActor> Bullets;

	//This allows me to change the direction value of any created bullet instances.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int Direction;

	//This allows me to change the Speedmodifier value of any created bullet instances.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float speedmodifier = 1;

	//This stores the time delay between bullets being shot.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float wait;

	//This stores the matieral that the bullet instance will recieve, and is set in editor.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UMaterialInterface* BulletMaterial;

	//This bool sets whether the turret can shoot or not.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool CanSpawn = false;

	//This is the function that spawns the bullets.
	UFUNCTION(BlueprintCallable)
		void ShootBullet();
};
