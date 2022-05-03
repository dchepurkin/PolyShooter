// PolyShooter By DChepurkin


#include "Animation/PSStartSetupMagazineAnimNotify.h"

void UPSStartSetupMagazineAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
										   const FAnimNotifyEventReference& EventReference)
{
	OnStartSetupMagazine.Broadcast(MeshComp);
}
