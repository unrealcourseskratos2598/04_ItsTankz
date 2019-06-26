// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"


/**
 * 
 */
UCLASS()
class ITZTANKZ_API ATankAIController : public AAIController
{
	GENERATED_BODY()

public:
	
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

protected:

	//Max proximity b/w AITank and PlayerTank before it stops moving.
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float AcceptanceRadius = 8000;


private:

	
};
