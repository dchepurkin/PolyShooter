// PolyShooter By DChepurkin

#include "Animation/PSAnimNotifyStateBase.h"

#include "PSWeaponComponent.h"

void UPSAnimNotifyStateBase::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration,
                                         const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);
	Begin(MeshComp);
}

void UPSAnimNotifyStateBase::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);
	End(MeshComp);
}

void UPSAnimNotifyStateBase::Begin(const USkeletalMeshComponent* MeshComp)
{
	const auto WeaponComponent = GetWeaponComponent(MeshComp);
	if(!WeaponComponent) return;

	OnNotifyBegin(WeaponComponent);
}

void UPSAnimNotifyStateBase::End(const USkeletalMeshComponent* MeshComp)
{
	const auto WeaponComponent = GetWeaponComponent(MeshComp);
	if(!WeaponComponent) return;

	OnNotifyEnd(WeaponComponent);
}

UPSWeaponComponent* UPSAnimNotifyStateBase::GetWeaponComponent(const USkeletalMeshComponent* MeshComp)
{
	const auto Actor = MeshComp->GetOwner();
	return Actor ? Actor->FindComponentByClass<UPSWeaponComponent>() : nullptr;
}
