// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"

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

ATankScript* ATankAIController::GetControlledTank() const
{
	return Cast<ATankScript>(GetPawn());
}

ATankScript* ATankAIController::GetPlayerTank() const
{

	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	return Cast<ATankScript>(PlayerPawn);

}

