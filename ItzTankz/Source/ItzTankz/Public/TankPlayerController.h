// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TankScript.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

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

	// Start moving the barrel of the PlayerTank so that
	// it points and shoots to where the crohair intersects the world.
	void AimTowardsCrosshair();

	
};
