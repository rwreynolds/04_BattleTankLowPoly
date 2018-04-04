// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Engine/World.h"
#include "Tank.h"


void ATankAIController::BeginPlay() {

	Super::BeginPlay();

}


void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto PlaerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());

	if (PlaerTank) {
		
		// TODO Move towards player tank

		// TODO Aim towards player tank
		auto ControlledTank = Cast<ATank>(GetPawn());
		ControlledTank->AimAt(PlaerTank->GetActorLocation());

		// TODO Fire if ready
		ControlledTank->Fire();

		return; 	
	}

	return;
}