// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/TargetPoint.h"
#include "Bomb.h"
#include "BombSpawn.generated.h"

UCLASS()
class FLINGSWINGWING_API ABombSpawn : public AActor
{
	GENERATED_BODY()


	
public:	
	// Sets default values for this actor's properties
	ABombSpawn();

	//This contains the trigger used for this script
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class USphereComponent* CollisionCollider;

	//This allows me to attatch a target point where the bombs will spawn
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ATargetPoint* Spawn;

	//This attatches the Bomb script to this script
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ABomb> Bomb;

	//This bool checks whether bombs can be spawned yet or not
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool CanSpawn;	

	//This stores the bomb instance that the script spawns
	UPROPERTY(EditAnywhere)
	class ABomb* InstanceBomb;

	//This contains the timer that the instance of the bomb should wait.
	UPROPERTY(EditAnywhere)
	float BombWait = 3;
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//This serves as a collision event for this object.
	UFUNCTION()
    void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);



};
