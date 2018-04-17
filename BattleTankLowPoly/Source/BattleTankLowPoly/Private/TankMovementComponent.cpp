// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"


void UTankMovementComponent::Initialize(UTankTrack* LefTrackToSet, UTankTrack* RightTrackToSet)
{
	LeftTrack = LefTrackToSet;
	RightTrack = RightTrackToSet;

	return;
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	if (!LeftTrack || !RightTrack) { return; }
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
	// TODO Fix doubled speed due to dual control use. 

	/*const FVector MoveVelocity;
	RequestDirectMove(MoveVelocity, false);*/
}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
	if (!LeftTrack || !RightTrack) { return; }
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
	// TODO Fix doubled speed due to dual control use. 

	/*const FVector MoveVelocity;
	RequestDirectMove(MoveVelocity, false);*/
}

void UTankMovementComponent::RequestDirectMove(const FVector & MoveVelocity, bool bForceMaxSpeed)
{
	// No need to call Super because of complete replacement of method

	auto TankForwardDirection = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto AIForwardIntention = MoveVelocity.GetSafeNormal();
	auto ForwardThrow = FVector::DotProduct(TankForwardDirection, AIForwardIntention);
	IntendMoveForward(ForwardThrow);

	/*auto TankName = GetOwner()->GetName();
	UE_LOG(LogTemp, Warning, TEXT("Tank %s dmove direction: %s"), *TankName, *(AIForwardIntention.ToString()));*/
}
