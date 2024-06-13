// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/TextRenderActor.h"
#include "BreakableBlock.generated.h"

UCLASS()
class FLINGSWINGWING_API ABreakableBlock : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABreakableBlock();

	//This contains the collision for this scripts block
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UBoxComponent* CollisionCollider;

	//This contains the trigger for the blocks
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UBoxComponent* TriggerCollider;

	//This containts the objects mesh.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* ObjectMesh;

	//This makes a timer which is called when the block is stood on
	UPROPERTY()
	FTimerHandle TimerHandle;

	//This is the time that the block needs to wait for before deactivating
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float BreakSpeed;

	//This bool is set to true when the object is hidden
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool Hidden = false;

	//This bool is set when the player enters the trigger
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool Triggered = false;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//This is used for collision events
	UFUNCTION()
    void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

//This function is called by a timer and deactivates the block
UFUNCTION()
void DeactivateBlock();

//This function is called by a timer and reactivates the block
UFUNCTION()
void ReactivateBlock();

};
