// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TankScript.generated.h"

//FowardDeclarations
class UTankBarrel;
class UTankTurret;
class UTankAimingComponent;
class UProjectileMovementComponent;
class UTankMovementComponent;

class AProjectile;

UCLASS()
class ITZTANKZ_API ATankScript : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATankScript();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UTankAimingComponent* TankAimingComponent = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = Input)
	UTankMovementComponent* TankMovementComponent = nullptr;

	

public:	
		
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void AimAt(FVector OutHitLocation);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetBarrelReference(UTankBarrel* BarrelToSet);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetTurretReference(UTankTurret* TurretToSet);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void Fire();

private:

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	TSubclassOf<AProjectile> ProjectileBlueprint;


	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float LaunchSpeed = 100000.f; // TODO find a sensible default value.

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float ReloadTimeInSeconds = 3;


	// Local Barrel reference for spawing projectile
	UTankBarrel* Barrel = nullptr;

	

	double LastFireTime = 0;


};
