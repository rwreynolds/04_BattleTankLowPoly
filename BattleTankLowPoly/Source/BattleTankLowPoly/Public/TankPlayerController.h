// Copyright Disrupting Inc 2018

#pragma once

#include "CoreMinimal.h"
#include "TankPlayerController.generated.h"


class UTankAimingComponent;

/**
 * Assists player in aiming
 */
UCLASS()
class BATTLETANKLOWPOLY_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

protected:
	UFUNCTION(BlueprintImplementableEvent, Category = Setup)
	void AimingComponentFound(UTankAimingComponent* AimCompRef);

private:
	UPROPERTY(EditDefaultsOnly)
	float CrossHairXLocation = 0.5;

	UPROPERTY(EditDefaultsOnly)
	float CrossHairYLocation = 0.33333;

	UPROPERTY(EditDefaultsOnly)
	float LineTraceRange = 1000000.0f;

	// Aim barrel through player tank crosshair
	void AimTowardsCrosshair();

	bool GetSightRayHitLocation(FVector& OutHitLocation) const;

	bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;

	bool GetLookVectorHitLocation(FVector LookDirection, FVector& OutHitLocation) const;
};
