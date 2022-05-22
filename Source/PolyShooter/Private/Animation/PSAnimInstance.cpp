// PolyShooter By DChepurkin

#include "Animation/PSAnimInstance.h"
#include "PSCharacterBase.h"
#include "PSWeaponBase.h"
#include "PSWeaponComponent.h"
#include "AnimGraphRuntime/Public/KismetAnimationLibrary.h"
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
	Direction = UKismetAnimationLibrary::CalculateDirection(Character->GetVelocity(), Character->GetActorRotation());
	IsJumping = GetIsJump();
	IsRuning = GetIsRuning();
	GetWeaponAnimData(WeaponAnimData);	
}

bool UPSAnimInstance::GetIsJump() const
{
	if(!Character) return false;

	const auto MovementComponent = Character->GetCharacterMovement();

	return MovementComponent && MovementComponent->IsFalling();
}

void UPSAnimInstance::GetWeaponAnimData(FWeaponAnimData& AnimData) const
{
	if(!Character) return;

	const auto WeaponComponent = Character->FindComponentByClass<UPSWeaponComponent>();
	if(!WeaponComponent) return;

	WeaponComponent->GetAnimData(AnimData);
}

bool UPSAnimInstance::GetIsRuning() const
{
	return Character && Character->IsRunning();
}
