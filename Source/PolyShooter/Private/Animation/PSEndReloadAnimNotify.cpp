// PolyShooter By DChepurkin


#include "Animation/PSEndReloadAnimNotify.h"

void UPSEndReloadAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
						const FAnimNotifyEventReference& EventReference)
{
	OnReloadFinished.Broadcast(MeshComp);
}