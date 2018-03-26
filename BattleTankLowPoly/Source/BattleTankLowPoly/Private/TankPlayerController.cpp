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

ATank* ATankPlayerController::getControlledTank() const {

	return(Cast<ATank>(GetPawn()));
	
};

