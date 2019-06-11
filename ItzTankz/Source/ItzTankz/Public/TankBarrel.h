// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ITZTANKZ_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()

public: 

	//-1 is max downward movement, +1 is max upward movement
	void Elevate(float RelativeSpeed);
	

private:

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float MaxDegreesPerSecond = 10.f; // Sensible default

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float MaxElevation = 30.f; // Sensible default

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float MinElevation = -10.f; // Sensible default



};
