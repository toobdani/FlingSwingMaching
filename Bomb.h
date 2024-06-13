// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlayerCharacter.h"
#include "Bomb.generated.h"

UCLASS()
class FLINGSWINGWING_API ABomb : public AActor
{
	GENERATED_BODY()

	
public:	
	// Sets default values for this actor's properties
	ABomb();
	
	//The trigger collision for this object
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class USphereComponent* CollisionCollider;
	
	//The mesh for this object, it is set as a sphere in the code
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* ObjectMesh;

	//The timer used for the bomb countdown
	UPROPERTY()
	FTimerHandle TimerHandle;

	//The float that stores the length of time before blowing up
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BlowUpTime = 3;

	//A bool which is set to true when the instance blows up
	UPROPERTY(EditAnywhere)
	bool blownup;

	//An variable connecting to the PlayerCharacter script
	UPROPERTY(VisibleAnywhere)
	class APlayerCharacter* MyChild;

	//A bool which when set to true will destroy the player when the bomb blows up
	UPROPERTY(EditAnywhere)
	bool DangerZone = false;

	//A bool used to start the bomb countdown
	UPROPERTY(EditAnywhere)
	bool StartBlowingUp = false;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//This function is called by the timer and blows up the bomb instance
	UFUNCTION()
	void BlowUp();

	//This serves as a collision event for this object.
	UFUNCTION()
    void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	//This serves to register events when someone exits the collision
	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

};
