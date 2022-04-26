// PolyShooter By DChepurkin

#include "Components/PSPlayerMovementComponent.h"
#include "GameFramework/Character.h"

DEFINE_LOG_CATEGORY_STATIC(LogPSPlayerMovement, All, All)

void UPSPlayerMovementComponent::MoveForward(float AxisValue) const
{
	if(!GetPawnOwner() || FMath::IsNearlyZero(AxisValue)) return;

	GetPawnOwner()->AddMovementInput(GetPawnOwner()->GetActorForwardVector(), AxisValue);
}

void UPSPlayerMovementComponent::MoveRight(float AxisValue) const
{
	if(!GetPawnOwner() || FMath::IsNearlyZero(AxisValue)) return;

	GetPawnOwner()->AddMovementInput(GetPawnOwner()->GetActorRightVector(), AxisValue);
}

