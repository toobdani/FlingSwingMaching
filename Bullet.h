// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bullet.generated.h"

UCLASS()
class FLINGSWINGWING_API ABullet : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABullet();

	//The trigger collision for this gameobject
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UBoxComponent* CollisionCollider;

	//A mesh for the sphere shape of the bullet.
	UPROPERTY(EditAnywhere)
		UStaticMesh* SphereMesh;

	//A mesh gameobject incase specific instances need a mesh
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* ObjectMesh;

	//A Vector containing the size that the instance should be.
	UPROPERTY(EditAnywhere)
		FVector ObjectSize = FVector(0.25f, 0.25f, 0.25f);

	//A vector containing the velocity that the bullets should move at.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector BulletVelocity;

	//A Vector containing the speed at which the velocity should be multiplied by
	UPROPERTY(EditAnywhere)
		float SpeedModifier;

	//An int whos value dictates the direction the bullet is shot at.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int Direction;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//This serves as a collision event for this object. 
	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	//This function is called each frame to make the bullet move
	void Moving(float DeltaTime);

	//This function is called to set the direction of the bullet.
	void SetDirection(int GoDirection, float SModifier);

};
