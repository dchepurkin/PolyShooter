// PolyShooter By DChepurkin

#include "Animation/PSAnimInstance.h"
#include "PSCharacterBase.h"
#include "GameFramework/CharacterMovementComponent.h"

void UPSAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Character = Cast<APSCharacterBase>(TryGetPawnOwner());
}

void UPSAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if(!Character) return;

	Velocity = Character->GetVelocity().Length();
	IsJump = GetIsJump();
}

bool UPSAnimInstance::GetIsJump() const
{
	if(!Character) return false;

	const auto MovementComponent = Character->GetCharacterMovement();
	if(!MovementComponent) return false;

	return MovementComponent->IsFalling();
}
