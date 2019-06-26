// Fill out your copyright notice in the Description page of Project Settings.


#include "TankScript.h"


// Sets default values
ATankScript::ATankScript()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
		
}

float ATankScript::GetHealthPercent()
{
	return (float)CurrentHealth / (float)StartHealth;
}

// Called when the game starts or when spawned
void ATankScript::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = StartHealth;

}



float ATankScript::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	int32 DamagePoints = FPlatformMath::RoundToInt(DamageAmount);
	int32 DamageToApply = FMath::Clamp<int32>(DamageAmount, 0, CurrentHealth);

	CurrentHealth -= DamageToApply;
	if (CurrentHealth <= 0)
	{
		OnDeath.Broadcast();
	}

	return DamageToApply;
}





