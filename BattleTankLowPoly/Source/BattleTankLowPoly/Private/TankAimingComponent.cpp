// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UTankAimingComponent::SetBarrelReference(UStaticMeshComponent* BarrelToSet) {
	Barrel = BarrelToSet;
}


void UTankAimingComponent::SetTurretReference(UStaticMeshComponent* TurretToSet)
{
	Turret = TurretToSet;
}


void UTankAimingComponent::AimAt(FVector HitLocation, float Launchspeed)
{
	if (!Barrel) { return; }

	auto BarrelLocation = Barrel->GetComponentLocation();

	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	// FVector EndLocation = (StartLocation + (HitLocation - StartLocation) * 0.9f); // An attempt to fix the full trace weirdness
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
		this,
		OutLaunchVelocity,
		StartLocation,
		HitLocation,
		Launchspeed,
		false,
		0.0f,
		0.0f,
		ESuggestProjVelocityTraceOption::DoNotTrace, //TraceFullPath causes weirdness,
		FCollisionResponseParams::DefaultResponseParam,
		TArray<AActor*>()/*,
		true*/
	);
	if(bHaveAimSolution) {

		auto AimDirection = OutLaunchVelocity.GetSafeNormal();		
		MoveBarrelTowards(AimDirection);
	}
	
	return;
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	
	
	

	// Workout difference between current barrel rotation, elevation, and aim direction elevation
	//auto CurrentBarrelRoatation1 = Barrel->GetForwardVector().Rotation();
	auto BarrelRoatator = Barrel->GetComponentRotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRoatator;

	// Move the barrel the required amount this frame
	// Given a max elevation speed, given frame rate


	auto TankName = GetOwner()->GetName();
	UE_LOG(LogTemp, Warning, TEXT("Tank %s Delta Rotation: %s"), *TankName, *(DeltaRotator.ToString()));
	//UE_LOG(LogTemp, Warning, TEXT("Tank %s move barrel to: %s"), *TankName, *(AimDirection.ToString()));
}

