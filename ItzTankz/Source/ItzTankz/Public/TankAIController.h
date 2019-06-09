// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

class ATankScript;

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

private:
	ATankScript* GetControlledTank() const;

	ATankScript* GetPlayerTank() const;

};
