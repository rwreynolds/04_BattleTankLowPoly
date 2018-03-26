// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"

void ATankAIController::BeginPlay() {

	Super::BeginPlay();

	auto PossesedTank = getControlledTank();
	/*if (!PossesedTank) {
		UE_LOG(LogTemp, Warning, TEXT("AIPlayerController BeginPlay: ControlledTank not found!"));
	} else {
		UE_LOG(LogTemp, Warning, TEXT("AIPlayerController BeginPlay: ControlledTank: %s"), *(PossesedTank->GetName()));
	}*/

	auto PlayerTank = getPlayerTank();
	if(!PlayerTank) {
		UE_LOG(LogTemp, Warning, TEXT("AIPlayerController BeginPlay: PlayerTank not found!"));
	} else {
		UE_LOG(LogTemp, Warning, TEXT("AIPlayerController BeginPlay: AITank: %s"), *(PossesedTank->GetName()));
		UE_LOG(LogTemp, Warning, TEXT("AITank has acquired FirstPlayer: PlayerTank: %s"), *(PlayerTank->GetName()));
		UE_LOG(LogTemp, Warning, TEXT("AITank has acquired FirstPlayer location: %s"), *(PlayerTank->GetActorLocation().ToString()));
	}
}

ATank* ATankAIController::getControlledTank() const {

	return(Cast<ATank>(GetPawn()));

}

ATank* ATankAIController::getPlayerTank() const
{

	return (Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn()));
	/*auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!PlayerPawn) {
		return nullptr;
	}
	else {
		return (Cast<ATank>(PlayerPawn));
	}*/

}


