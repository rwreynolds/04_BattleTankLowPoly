// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Engine/World.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet) {
	Barrel = BarrelToSet;
	return;
}


void UTankAimingComponent::SetTurretReference(UTankTurret* TurretToSet)
{
	Turret = TurretToSet;
	return;
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
		ESuggestProjVelocityTraceOption::DoNotTrace, //TraceFullPath causes weirdness, parm must be present to fix UE bug
		FCollisionResponseParams::DefaultResponseParam,
		TArray<AActor*>()/*,
		true*/
	);
	if(bHaveAimSolution) {

		auto AimDirection = OutLaunchVelocity.GetSafeNormal();		
		MoveBarrelTowards(AimDirection);

		/*auto DeltaTime = GetWorld()->GetTimeSeconds();
		auto TankName = GetOwner()->GetName();
		UE_LOG(LogTemp, Warning, TEXT("Tank %s Aim direction is %s @ %f seconds"), *TankName, *(AimDirection.ToString()), DeltaTime);*/
	}
	
	return;
}


void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	
	// Workout difference between current barrel rotation, elevation, and aim direction elevation
	auto BarrelRoatator = Barrel->GetComponentRotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRoatator;

	Barrel->Elevate(DeltaRotator.Pitch);
	Turret->Rotate(DeltaRotator.Yaw);

	return;
}


