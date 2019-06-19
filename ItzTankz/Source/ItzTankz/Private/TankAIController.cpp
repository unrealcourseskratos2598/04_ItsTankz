// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"
#include "TankAimingComponent.h"
// Depends on movement component via pathfinding system

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// TODO Move towards the player

	// Aim towards the player
	auto ControlledTank = GetPawn();
	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();

	if (!ensure(PlayerTank && ControlledTank)) { return; }
	
	//Move Towards the Player
	MoveToActor(PlayerTank, AcceptanceRadius);
	auto ControlledTankAimingComp = ControlledTank->FindComponentByClass<UTankAimingComponent>();
	ControlledTankAimingComp->AimAt(PlayerTank->GetActorLocation());

	// TODO Fix Firing
	ControlledTankAimingComp->Fire();

	
		
}

