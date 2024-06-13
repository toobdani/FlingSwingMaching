// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DestroyableObject.generated.h"

UCLASS()
class FLINGSWINGWING_API ADestroyableObject : public AActor
{
	GENERATED_BODY()
	
	
public:	
	// Sets default values for this actor's properties
	ADestroyableObject();

	//The trigger collision for this gameobject
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
    class UBoxComponent* CollisionCollider;

	//A mesh gameobject incase specific instance needs a mesh
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* ObjectMesh; 

	//This int stores the number at which the PlayerCharacter script's charge int must reach/exceed to destroy the object
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int BreakCount;

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
