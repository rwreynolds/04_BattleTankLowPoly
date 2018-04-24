// Copyright Disrupting Inc 2018

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
	if(!ensure(LeftTrack && RightTrack)) { return; }
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);

	return;
}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
	if(!ensure(LeftTrack && RightTrack)) { return; }
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);

	return;
}

void UTankMovementComponent::RequestDirectMove(const FVector & MoveVelocity, bool bForceMaxSpeed)
{
	// No need to call Super because of complete replacement of method

	auto TankForwardDirection = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto AIForwardIntention = MoveVelocity.GetSafeNormal();
	
	auto ForwardThrow = FVector::DotProduct(TankForwardDirection, AIForwardIntention);
	IntendMoveForward(ForwardThrow);

	auto RightThrow = FVector::CrossProduct(TankForwardDirection, AIForwardIntention).Z;
	IntendTurnRight(RightThrow);

	/*auto TankName = GetOwner()->GetName();
	UE_LOG(LogTemp, Warning, TEXT("Right: %f, Forward: %f"), RightThrow, ForwardThrow);*/
}
