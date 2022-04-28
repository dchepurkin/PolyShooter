// PolyShooter By DChepurkin

#include "Components/PSPlayerMovementComponent.h"

#include "PSPlayerCharacter.h"

DEFINE_LOG_CATEGORY_STATIC(LogPSPlayerMovement, All, All)

float UPSPlayerMovementComponent::GetMaxSpeed() const
{
	const auto Character = GetOwner<APSPlayerCharacter>();
	if(!Character) return Super::GetMaxSpeed();

	return Character->IsRunning() ? RunSpeedModifier * Super::GetMaxSpeed() : Super::GetMaxSpeed();
}
