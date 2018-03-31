// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet) {
	Barrel = BarrelToSet;
}


void UTankAimingComponent::SetTurretReference(UTankBarrel* TurretToSet)
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
		TArray<AActor*>(),
		true
	);
	if(bHaveAimSolution) {

		auto AimDirection = OutLaunchVelocity.GetSafeNormal();		
		MoveBarrelTowards(AimDirection);

		auto DeltaTime = GetWorld()->GetTimeSeconds();
		auto TankName = GetOwner()->GetName();
		UE_LOG(LogTemp, Warning, TEXT("Tank %s Aim direction is %s @ %f seconds"), *TankName, *(AimDirection.ToString()), DeltaTime);
		//UE_LOG(LogTemp, Warning, TEXT("Tank %s move barrel to: %s"), *TankName, *(AimDirection.ToString()));
	} else {
		auto DeltaTime = GetWorld()->GetTimeSeconds();
		auto TankName = GetOwner()->GetName();
		UE_LOG(LogTemp, Warning, TEXT("Tank %s solution not found @ %f seconds"), *TankName, DeltaTime);
		//UE_LOG(LogTemp, Warning, TEXT("Tank %s move barrel to: %s"), *TankName, *(AimDirection.ToString()));
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

	Barrel->Elevate(5);
}

