// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Engine/World.h"
#include "GameFramework/Controller.h"
#include "TankAimingComponent.h"

void ATankPlayerController::BeginPlay() {

	Super::BeginPlay();
	
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if(ensure(AimingComponent)) {
		AimingComponentFound(AimingComponent);
	}
}


void ATankPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick( DeltaSeconds );
	
	AimTowardsCrosshair();
}


void ATankPlayerController::AimTowardsCrosshair()
{
	
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }

	FVector HitLocation; 	
	if(GetSightRayHitLocation(HitLocation)) {
		AimingComponent->AimAt(HitLocation);
	}
	return;
}


// Get world location of line trace through crosshair, returns true if hits the landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
	// Find the crosshair position in pixel coordinates
	int32 ViewpoerSizeX, ViewpoertSizeY;
	GetViewportSize(ViewpoerSizeX, ViewpoertSizeY);
	auto ScreenLocation = FVector2D(ViewpoerSizeX * CrossHairXLocation, ViewpoertSizeY* CrossHairYLocation);
	
	// "de=project" the screen position of the crosshair to a world position
	FVector LookDirection;
	if(GetLookDirection(ScreenLocation, LookDirection)) {
		// Line-trace along that look direction, and see what we hit (up to some max range).
		// if ray-cast hits landscape 
			// store location in OutHitLocation and return true
		if(GetLookVectorHitLocation(LookDirection, OutHitLocation)) {
			return true;
		}
	}
	return false;
}


bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& OutHitLocation) const
{
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = (StartLocation + (LookDirection * LineTraceRange));
	FCollisionQueryParams QueryCollisionParams;
	if(GetWorld()->LineTraceSingleByChannel(
			HitResult,
			StartLocation,
			EndLocation,
			ECollisionChannel::ECC_Visibility,
			QueryCollisionParams)
		) {
			OutHitLocation = HitResult.Location;
			return true;
		  }
	OutHitLocation = FVector(0);
	return false;
}


bool ATankPlayerController::GetLookDirection(FVector2D const ScreenLocation, FVector& LookDirection) const
{
	FVector CameraWorldLocation; // Discarded camers position
	return DeprojectScreenPositionToWorld(
		ScreenLocation.X, 
		ScreenLocation.Y, 
		CameraWorldLocation, 
		LookDirection);
}

