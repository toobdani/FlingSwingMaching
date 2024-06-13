// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Respawn.generated.h"

UCLASS()
class FLINGSWINGWING_API ARespawn : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARespawn();

	//The trigger collision for this gameobject
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UBoxComponent* CollisionCollider;

	//A mesh gameobject incase specific respawns need a mesh
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* ObjectMesh;

	//A Vector which contains the checkpoint that individuals triggers may represent, is changed in editor.
	UPROPERTY(EditAnywhere)
		FVector Checkpoint;

	//This bool checks whether the instance of the script is a damage trigger or checkpoint trigger. 
	//true then the trigger is a checkpoint, if false it is a damage trigger.
	UPROPERTY(EditAnywhere)
		bool SpawnorSave;

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
