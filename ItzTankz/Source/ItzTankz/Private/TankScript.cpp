// Fill out your copyright notice in the Description page of Project Settings.


#include "TankScript.h"
#include "TankAimingComponent.h"

// Sets default values
ATankScript::ATankScript()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// No need to protect pointer as added at construction
	TankAimingComponent = CreateAbstractDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));

}

// Called when the game starts or when spawned
void ATankScript::BeginPlay()
{
	Super::BeginPlay();
	
}


// Called to bind functionality to input
void ATankScript::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATankScript::AimAt(FVector OutHitLocation)
{
	TankAimingComponent->AimAt(OutHitLocation, LaunchSpeed);
	
}

void ATankScript::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	TankAimingComponent->SetBarrelReference(BarrelToSet);
}

void ATankScript::SetTurretReference(UTankTurret* TurretToSet)
{
	TankAimingComponent->SetTurretReference(TurretToSet);
}


