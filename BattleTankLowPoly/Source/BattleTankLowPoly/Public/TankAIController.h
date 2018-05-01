// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"


class UTankAimingComponent;

class ATank;
/**
 * 
 */
UCLASS()
class BATTLETANKLOWPOLY_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
private:

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;
	
	ATank * GetControlledTank() const;

	ATank * GetPlayerTank() const;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float AcepptanceRadius = 3000.0f; // Limits AI distance from player. Assuming cm.

protected:
	UFUNCTION(BlueprintImplementableEvent, Category = Setup)
	void AimingComponentFound(UTankAimingComponent* AimCompRef);
};
