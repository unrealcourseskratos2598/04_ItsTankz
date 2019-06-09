// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"
#include "TankScript.h"
#include "Engine/World.h"


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

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

ATankScript* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATankScript>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{

	if (!GetControlledTank()) {	return;	}

	FVector OutHitLocation; // Out Parameter
	if (GetSightRayHitLocation(OutHitLocation)) // Has a "side-effect", is going to line-trace
	{
		GetControlledTank()->AimAt(OutHitLocation);

		// TODO Tell the controlled tank to aim at this point
		
	}
	
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
	// Find the crosshair position
	int32 ViewportSizeX, ViewportSizeY;	

	GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto ScreenLocation = FVector2D(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);

	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		// Line-trace along the LookDIrection, and see what we hit (up to a max range)
		return GetLookVectorHitLocation(OutHitLocation, LookDirection);
	}

	return false;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
	FVector CamWorldLocation; // To be discarded
	return DeprojectScreenPositionToWorld(
		ScreenLocation.X,
		ScreenLocation.Y,
		CamWorldLocation,
		LookDirection
	);
	
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector& OutHitLocation, FVector LookDirection) const
{
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection * LineTraceRange);
	FHitResult OutHitResult;

	if (GetWorld()->LineTraceSingleByChannel(
		OutHitResult,
		StartLocation,
		EndLocation,
		ECollisionChannel::ECC_Camera		
	))
	{
		OutHitLocation = OutHitResult.Location;
		return true;
	}
	OutHitLocation = FVector(0);
	return false;
	
}
