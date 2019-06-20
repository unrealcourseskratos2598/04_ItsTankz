// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::Initialise(UTankTurret* TurretToSet, UTankBarrel* BarrelToSet)
{

	Barrel = BarrelToSet;
	Turret = TurretToSet;

}


void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// Wait time before 1st shot
	LastFireTime = FPlatformTime::Seconds();
}

void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if ((FPlatformTime::Seconds() - LastFireTime) < ReloadTimeInSeconds)
	{
		FiringStatus = EFiringStatus::Reloading;
	}
	else if (IsBarrelMoving())
	{
		FiringStatus = EFiringStatus::Aiming;
	}
	else
	{
		FiringStatus = EFiringStatus::Locked;
	}
}

void UTankAimingComponent::AimAt(FVector OutHitLocation)
{
	if (!ensure(Barrel && Turret)) { return; }

	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity
	(
		this,
		OutLaunchVelocity,
		StartLocation,
		OutHitLocation,
		LaunchSpeed,
		false,										// Parameter is optional still neccessary (BUG!!)
		0,											// Parameter is optional still neccessary (BUG!!)
		0,											// Parameter is optional still neccessary (BUG!!)
		ESuggestProjVelocityTraceOption::DoNotTrace // Parameter is optional still neccessary (BUG!!)
	);

	if (bHaveAimSolution)
	{
		AimDirection = OutLaunchVelocity.GetSafeNormal();	
		MoveBarrelTowards(AimDirection);
		auto Time = GetWorld()->GetTimeSeconds();		
	}
	else
	{
		auto Time = GetWorld()->GetTimeSeconds();		
	}
	// If no sultion found do nothing
}

void UTankAimingComponent::MoveBarrelTowards(FVector _AimDirection)
{
	if (!ensure(Barrel && Turret)) { return; }

	//Work out the difference between current barrel rotation an AimDirection
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = _AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;	

	Barrel->Elevate(DeltaRotator.Pitch);
	Turret->Rotate(DeltaRotator.Yaw);
}

bool UTankAimingComponent::IsBarrelMoving()
{
	if (!ensure(Barrel)) { return false; }

	auto BarrelForwardVector = Barrel->GetForwardVector();

	return !BarrelForwardVector.Equals(AimDirection, 0.01f);	
}

void UTankAimingComponent::Fire()
{
	
	if (FiringStatus != EFiringStatus::Reloading)
	{
		// Spawn a projectile at the socket location on the barrel
		if (!ensure(Barrel)) { return; }
		if (!ensure(ProjectileBlueprint)) { return; }
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile"))
			);

		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
	}
}



