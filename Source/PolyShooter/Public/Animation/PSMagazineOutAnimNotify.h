// PolyShooter By DChepurkin

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "PSMagazineOutAnimNotify.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnMagazineOutSignature, USkeletalMeshComponent*)

UCLASS()
class POLYSHOOTER_API UPSMagazineOutAnimNotify : public UAnimNotify
{
	GENERATED_BODY()

public:
	FOnMagazineOutSignature OnMagazineOut;

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	                    const FAnimNotifyEventReference& EventReference) override;
};
