// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlayerPlatform.h"
#include "P_Platform_Restart.generated.h"

UCLASS()
class FLINGSWINGWING_API AP_Platform_Restart : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AP_Platform_Restart();

	//This stores the Start location of any attatched PlayerPlatforms.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector StartLocation;

	//This stores an instance of PlayerPlatforms attatched to the script in the editor.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class APlayerPlatform* InstancePlatform;
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//This function is called from blueprints and resets the location of the platform.
	UFUNCTION(BlueprintCallable)
	void RestartLocation();

};
