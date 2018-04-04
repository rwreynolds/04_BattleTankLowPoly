// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * TankTrack is used to set movement parameters for, and move the tank
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANKLOWPOLY_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:

	// Set hrottle between +1 and -1
	UFUNCTION(BlueprintCallable, Category = Input)
	void SetThrottle(float Throttle);

	// Max force per track in Newtons (Force = Mass(kg) * Accelration(m/s^s))
	UPROPERTY(EditDefaultsOnly)
	float TrackMaxDrivingForce = 400000.0f; // Assuming 40,000kg mass @ 10m/s^2 (1g) accelration
	
	
};
