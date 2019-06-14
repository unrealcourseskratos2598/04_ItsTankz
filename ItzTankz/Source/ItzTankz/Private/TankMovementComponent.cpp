// Fill out your copyright notice in the Description page of Project Settings.


#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
	if (!LeftTrackToSet || !RightTrackToSet) { return; }

	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	// No need for Super as we are replacing the functionality
	auto TankForward = GetOwner()->GetActorForwardVector();
	auto AIForwardIntention = MoveVelocity.GetSafeNormal();

	auto AIThrowForward = FVector::DotProduct(TankForward, AIForwardIntention);

	IntendMoveForward(AIThrowForward);

	auto AIThrowRight = FVector::CrossProduct(TankForward, AIForwardIntention).Z;
	IntendTurnRight(AIThrowRight);
		
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	
	if (!LeftTrack || !RightTrack) { return; }
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);

	// TODO prevent double-speed due to multi-input

}

void UTankMovementComponent::IntendMoveBackward(float Throw)
{

	if (!LeftTrack || !RightTrack) { return; }
	LeftTrack->SetThrottle(-Throw);
	RightTrack->SetThrottle(-Throw);

	// TODO prevent double-speed due to multi-input

}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
	if (!LeftTrack || !RightTrack) { return; }
	LeftTrack->SetThrottle(-Throw);
	RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendTurnLeft(float Throw)
{
	if (!LeftTrack || !RightTrack) { return; }
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
}
