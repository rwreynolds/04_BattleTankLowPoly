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

	auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());

	if(ensure(PlayerTank)) {
		
		// TODO Move towards player tank
		MoveToActor(PlayerTank, AcepptanceRadius);

		// TODO Aim towards player tank
		auto ControlledTank = Cast<ATank>(GetPawn());
		ControlledTank->AimAt(PlayerTank->GetActorLocation());

		// TODO Fire if ready
		ControlledTank->Fire();

		return; 	
	}

	return;
}