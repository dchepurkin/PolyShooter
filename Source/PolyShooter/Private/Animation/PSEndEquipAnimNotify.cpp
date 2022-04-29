// PolyShooter By DChepurkin

#include "Animation/PSEndEquipAnimNotify.h"

DEFINE_LOG_CATEGORY_STATIC(LogPSEndEquipAnimNotify, All, All)

void UPSEndEquipAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                   const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	OnEquipFinished.Broadcast(MeshComp);
}
