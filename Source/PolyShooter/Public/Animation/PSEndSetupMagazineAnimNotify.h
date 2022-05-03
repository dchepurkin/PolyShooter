// PolyShooter By DChepurkin

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "PSEndSetupMagazineAnimNotify.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnEndSetupMagazineSignature, USkeletalMeshComponent*)

UCLASS()
class POLYSHOOTER_API UPSEndSetupMagazineAnimNotify : public UAnimNotify
{
	GENERATED_BODY()

public:
	FOnEndSetupMagazineSignature OnEndSetupMagazine;

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	                    const FAnimNotifyEventReference& EventReference) override;
};
