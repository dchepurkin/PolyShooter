// PolyShooter By DChepurkin

#include "Animation/PSEndSetupMagazineAnimNotify.h"

void UPSEndSetupMagazineAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                           const FAnimNotifyEventReference& EventReference)
{
	OnEndSetupMagazine.Broadcast(MeshComp);
}
