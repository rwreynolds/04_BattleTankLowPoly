// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay() {

	Super::BeginPlay();
	
	auto PossesedTank = getControlledTank();
	if (!PossesedTank) {
		UE_LOG(LogTemp, Warning, TEXT("PlayerController BeginPlay: ControlledTank not found!"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("PlayerController BeginPlay: ControlledTank: %s"), *(PossesedTank->GetName()));
	}

}

void ATankPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick( DeltaSeconds );
	AimTowardsCrosshair();

}

ATank* ATankPlayerController::getControlledTank() const {

	return(Cast<ATank>(GetPawn()));
	
}

void ATankPlayerController::AimTowardsCrosshair()
{

	if (!getControlledTank) { return; }

	// Get world location if line trace through crosshair
	// If it hits the landscape
		// Tell controlled tank to aim at this point

	return;
}

