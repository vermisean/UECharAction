// Copyright Sean Duffy 2018

#include "PlayerCharacterMovementComponent.h"
#include "PlayerCharacter.h"



float UPlayerCharacterMovementComponent::GetMaxSpeed() const
{
	float MaxSpeed = Super::GetMaxSpeed();

	const APlayerCharacter* CharOwner = Cast<APlayerCharacter>(PawnOwner);
	if (CharOwner)
	{
		if (CharOwner->IsSprinting())
		{
			MaxSpeed *= CharOwner->GetSprintSpeedModifier();
		}
	}

	return MaxSpeed;
}
