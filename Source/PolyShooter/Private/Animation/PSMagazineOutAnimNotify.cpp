// PolyShooter By DChepurkin


#include "Animation/PSMagazineOutAnimNotify.h"

void UPSMagazineOutAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
										   const FAnimNotifyEventReference& EventReference)
{
	OnMagazineOut.Broadcast(MeshComp);
}