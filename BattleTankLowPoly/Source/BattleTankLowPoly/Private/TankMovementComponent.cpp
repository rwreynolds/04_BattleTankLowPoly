// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	//UE_LOG(LogTemp, Warning, TEXT("Intend move forward throw: %f"), Throw);

	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);

}

void UTankMovementComponent::Initialize(UTankTrack* LefTrackToSet, UTankTrack* RightTrackToSet)
{
	if (!LefTrackToSet || !RightTrackToSet) { return; }

	LeftTrack = LefTrackToSet;
	RightTrack = RightTrackToSet;
	// TODO Fix doubled speed due to dual control use. 

	return;
}
