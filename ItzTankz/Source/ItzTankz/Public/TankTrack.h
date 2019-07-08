// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * TankTrack is used to set maximum driving force, and to apply the forces to the tank.
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent)) 
class ITZTANKZ_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	
	// Sets a throttle between -1 & +1
	UFUNCTION(BlueprintCallable, Category = "Input")
	void SetThrottle(float Throttle);

	


	// Max force per track, in Newtons
	UPROPERTY(EditDefaultsOnly)
	float TrackMaxDrivinggForce = 400000;  // Tank mass = 40 tonnes & 1G acceleration

private:

	UTankTrack();
	
	TArray<class ASprungWheel*> GetWheels() const;
		
	void DriveTrack(float CurrentThrottle);
	
};
