// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "Engine/World.h"
#include "math.h"
#include "TankAimingComponent.h"
#include "TankMovementComponent.h"
#include "TankBarrel.h"
#include "Projectile.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// No need to protect pointers as added at construction. Not wrapped in if()
	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
	TankMovementComponent = CreateDefaultSubobject<UTankMovementComponent>(FName("Movement Component"));
}


// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
	ReadyToFire = GetWorld()->GetTimeSeconds() + FMath::RandRange(0.0f, ReloadTimeInSeconds); //ReloadTimeInSeconds;
}


// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}


void ATank::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	TankAimingComponent->SetBarrelReference(BarrelToSet);
	Barrel = BarrelToSet;

	return;
}


void ATank::SetTurretReference(UTankTurret* TurretToSet)
{
	TankAimingComponent->SetTurretReference(TurretToSet);
}


void ATank::AimAt(FVector HitLocation)
{
	TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
	
	//UE_LOG(LogTemp, Warning, TEXT("Delta time: %f"), DeltaTime);

	return;
}

void ATank::Fire()
{	
	bool isReloaded = (FPlatformTime::Seconds() - ReadyToFire) >= (double)ReloadTimeInSeconds;
	if (Barrel && isReloaded) {

		// Spawn projectile at socket location and launch
		const FVector SocketLocation = Barrel->GetSocketLocation(FName("Projectile"));
		const FRotator SocketRotation = Barrel->GetSocketRotation(FName("Projectile"));
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
				ProjectileBlueprint,
				Barrel->GetSocketLocation(FName("Projectile")),
				Barrel->GetSocketRotation(FName("Projectile"))
			);
		Projectile->LaunchProjectile(LaunchSpeed);

		ReadyToFire = FPlatformTime::Seconds() + (double)FMath::RandRange(0.0f, ReloadTimeInSeconds);

	}

	return;
}

