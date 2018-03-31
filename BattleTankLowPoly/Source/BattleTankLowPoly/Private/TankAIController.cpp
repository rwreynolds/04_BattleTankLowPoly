// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Engine/World.h"
#include "Tank.h"

void ATankAIController::BeginPlay() {

	Super::BeginPlay();

	auto PossesedTank = GetControlledTank();
	/*if (!PossesedTank) {
		UE_LOG(LogTemp, Warning, TEXT("AIPlayerController BeginPlay: ControlledTank not found!"));
	} else {
		UE_LOG(LogTemp, Warning, TEXT("AIPlayerController BeginPlay: ControlledTank: %s"), *(PossesedTank->GetName()));
	}*/

	auto PlayerTank = GetPlayerTank();
	if(!PlayerTank) {
		UE_LOG(LogTemp, Warning, TEXT("AIPlayerController BeginPlay: PlayerTank not found!"));
	} else {
		UE_LOG(LogTemp, Warning, TEXT("AIPlayerController BeginPlay: AITank: %s"), *(PossesedTank->GetName()));
		UE_LOG(LogTemp, Warning, TEXT("AITank has acquired FirstPlayer: PlayerTank: %s"), *(PlayerTank->GetName()));
		UE_LOG(LogTemp, Warning, TEXT("AITank has acquired FirstPlayer location: %s"), *(PlayerTank->GetActorLocation().ToString()));
	}
}

void ATankAIController::Tick(float DeltaTime)
{

	Super::Tick(DeltaTime);

	if (GetPlayerTank()) {

		GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());
		
		// TODO Move towards player tank

		// TODO Aim towards player tank

		// TODO Fire if ready

		return; 	
	}

	
	return;
}

ATank* ATankAIController::GetControlledTank() const {

	return(Cast<ATank>(GetPawn()));

}

ATank* ATankAIController::GetPlayerTank() const
{

	return (Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn()));

}


