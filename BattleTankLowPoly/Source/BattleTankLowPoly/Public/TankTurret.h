// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTurret.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent)) // ,hidecategories("Collision") - This can be used to hide Blueprint details
class BATTLETANKLOWPOLY_API UTankTurret : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	void Rotate(float RelativeSpeed);

private:
	// -1 is max down and +1 is max up
	UPROPERTY(EditDefaultsOnly, Category = Setup)
		float MaxDegreesPerSecond = 5.0f;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
		float MaxRotationDegrees = 180.0f;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
		float MinRotationDegrees = 0.0f;
	
	
};
