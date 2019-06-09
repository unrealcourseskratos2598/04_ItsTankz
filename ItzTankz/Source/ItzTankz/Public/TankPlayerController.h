// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/World.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class ATankScript;

/**
 * 
 */
UCLASS()
class ITZTANKZ_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ATankScript* GetControlledTank() const;
		
	virtual void BeginPlay() override;

	virtual void Tick(float) override;

private:

	UPROPERTY(EditAnywhere)
	float CrossHairXLocation = 0.5f;

	UPROPERTY(EditAnywhere)
	float CrossHairYLocation = 0.33333f;

	UPROPERTY(EditAnywhere)
		float LineTraceRange = 1000000.f;

	// Start moving the barrel of the PlayerTank so that
	// it points and shoots to where the crohair intersects the world.
	void AimTowardsCrosshair();

	// Return an OUT parameter, true if hits landscape
	bool GetSightRayHitLocation(FVector& OutHitLocation) const;
	
	bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;

	bool GetLookVectorHitLocation(FVector& OutHitLocation, FVector LookDirection) const;
};
