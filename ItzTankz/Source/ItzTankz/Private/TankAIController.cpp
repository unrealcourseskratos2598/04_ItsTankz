// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"
#include "TankScript.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// TODO Move towards the player

	// Aim towards the player
	auto ControlledTank = Cast<ATankScript>(GetPawn());
	auto PlayerTank = Cast<ATankScript>(GetWorld()->GetFirstPlayerController()->GetPawn());

	if (PlayerTank)
	{
		//Move Towards the Player
		MoveToActor(PlayerTank, AcceptanceRadius);

		ControlledTank->AimAt(PlayerTank->GetActorLocation());

		// Fire when ready
		ControlledTank->Fire();

	}

	
	
	
}

