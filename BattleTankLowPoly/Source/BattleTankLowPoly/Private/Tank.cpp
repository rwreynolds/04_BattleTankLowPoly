// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "Engine/World.h"
#include "math.h"
#include "TankBarrel.h"
#include "Projectile.h"

// Sets default values
ATank::ATank()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	/*auto name = GetName();
	UE_LOG(LogTemp, Warning, TEXT("[%s] 57d629b7-code: Tank Constructor"), *name);*/
}

void ATank::BeginPlay()
{
	Super::BeginPlay();

	//Barrel = FindComponentByClass<UTankBarrel>();
	/*auto name = GetName();
	UE_LOG(LogTemp, Warning, TEXT("[%s] 57d629b7-code: Begin Play"), *name);*/
}


void ATank::Fire()
{	
	if(!ensure(Barrel)) { return; }

	bool isReloaded = (FPlatformTime::Seconds() - ReadyToFire) >= (double)ReloadTimeInSeconds;
	if(isReloaded) {

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

