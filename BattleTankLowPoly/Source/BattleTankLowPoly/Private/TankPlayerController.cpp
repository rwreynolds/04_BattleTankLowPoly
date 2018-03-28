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

	if (!getControlledTank()) { return; }

	FVector OutHitLocation; // { 0.0, 0.0, 0.0 }; // Output parameter
	//UE_LOG(LogTemp, Warning, TEXT("HitLocation In: %s"), *(OutHitLocation.ToString()));
	
	if (GetSightRayHitLocation(OutHitLocation)) {
		//UE_LOG(LogTemp, Warning, TEXT("Look direction: %s"), *(OutHitLocation.ToString()));	
		//TODO Tell controlled tank to aim at this point
	}

	return;
}

// Get world location of line trace through crosshair, returns true if hits the landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
	OutHitLocation = (GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation());

	// Find the crosshair position in pixel coordinates
	int32 ViewpoerSizeX, ViewpoertSizeY;
	GetViewportSize(ViewpoerSizeX, ViewpoertSizeY);
	auto ScreenLocation = FVector2D(ViewpoerSizeX * CrossHairXLocation, ViewpoertSizeY * CrossHairYLocation);
	
	// "de=project" the screen position of the crosshair to a world position
	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection)) {
		UE_LOG(LogTemp, Warning, TEXT("Sight look direction: %s"), *(LookDirection.ToString()));
	}

	// Line-trace along that look direction, and see what we hit (up to some max range).
	// if ray-cast hits landscape 
		// store location in OutHitLocation and return true

	return true;
}

bool ATankPlayerController::GetLookDirection(FVector2D const ScreenLocation, FVector& LookDirection) const
{
	FVector CameraWorldLocation;
	return DeprojectScreenPositionToWorld(
		ScreenLocation.X, 
		ScreenLocation.Y, 
		CameraWorldLocation, 
		LookDirection);
}

