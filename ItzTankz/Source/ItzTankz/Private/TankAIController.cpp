// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"
#include "TankScript.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	auto PlayerTank = GetPlayerTank();
	if (!PlayerTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController cannot find Playertank!"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController has found : %s"), *PlayerTank->GetName());
	}
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// TODO Move towards the player

	// Aim towards the player
	if (GetPlayerTank())
	{
		GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());
	}

	// Fire when ready	
	
}

ATankScript* ATankAIController::GetControlledTank() const
{
	return Cast<ATankScript>(GetPawn());
}

ATankScript* ATankAIController::GetPlayerTank() const
{

	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	return Cast<ATankScript>(PlayerPawn);

}

