// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovingPlatform.generated.h"

UCLASS()
class FLINGSWINGWING_API AMovingPlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMovingPlatform();

	//The collision for this gameobject
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UBoxComponent* CollisionCollider;

	//A mesh gameobject
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* ObjectMesh;

	//One of two bools used to check if the platform is moving
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool BeginMoving = false;

	//The second of two platforms to check whether the platform should be moving
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool Movebool;

	//The velocity at which the platform moves, and in what direction it should move
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector PlatformVelocity;

	//The location of the platform at the start of its movement
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector Start = FVector(100., 0., 0.);

	//The distance the platform moves for
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MoveDistance = 200;

	//A float which is added to during delays to calculate how long the wait should be
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float DelayTime = 0.;

	//The value that the DelayTime float should reach/exceed in order for the delay to end.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float wait;

	//When this bool is set, it means the platform will wait a bit before moving again.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool Pause;

	//This bool is set true during delays, and stops the platform from moving.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool StopMove;


private:
//This function allows the platform to move and is called each frame
	void MovePlatform(float DeltaTime);

//This bool function is used to check whether the platform is ready to move back
	bool TurnBack() const;

//This function is used to delay the platform in between movements
	void Delay(float DeltaTime);

//This float is used to measure the distance the platform has moved
	float GetDistanceMoved() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
