// PolyShooter By DChepurkin

#include "Animation/PSEndFireAnimNotify.h"

void UPSEndFireAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                  const FAnimNotifyEventReference& EventReference)
{
	OnFireFinished.Broadcast(MeshComp);
}
