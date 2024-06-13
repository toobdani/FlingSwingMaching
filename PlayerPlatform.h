// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlayerPlatform.generated.h"

UCLASS()
class FLINGSWINGWING_API APlayerPlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlayerPlatform();

	//The collision for this gameobject
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UBoxComponent* CollisionCollider;

	//The trigger collision for this gameobject
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UBoxComponent* TriggerCollider;

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

private:
//This function allows the platform to move and is called each frame
void MovePlatform(float DeltaTime);

	//This bool function is used to check whether the platform is ready to move back
	bool TurnBack() const;

	//This float is used to measure the distance the platform has moved
	float GetDistanceMoved() const;

//This serves as a collision event for this object.
UFUNCTION()
    void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

//This serves to register events when someone exits the collision
UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
