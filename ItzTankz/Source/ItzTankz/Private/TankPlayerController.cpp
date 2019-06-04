// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"



void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto ControlledTank = GetControlledTank();
	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController not possessing a tank!"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController is possessing : %s"), *ControlledTank->GetName());
	}
}

// Tick
	//Super..
	// AimTowardsCrosshair();
void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair()
{

	if (!GetControlledTank()) {	return;	}

	//Get world location if linetrace through crosshair
	// If it hits the landscape
		// Tell the controlled tank to aim at this point

}


ATankScript* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATankScript>(GetPawn());
}

