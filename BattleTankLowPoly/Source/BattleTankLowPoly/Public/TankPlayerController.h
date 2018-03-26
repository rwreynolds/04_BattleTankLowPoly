// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANKLOWPOLY_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	ATank* getControlledTank() const;

private:

	// Aim barrel through player tank crosshair
	void AimTowardsCrosshair();

};
