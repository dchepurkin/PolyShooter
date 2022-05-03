// PolyShooter By DChepurkin

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "PSStartSetupMagazineAnimNotify.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnStartSetupMagazineSignature, USkeletalMeshComponent*)

UCLASS()
class POLYSHOOTER_API UPSStartSetupMagazineAnimNotify : public UAnimNotify
{
	GENERATED_BODY()

public:
	FOnStartSetupMagazineSignature OnStartSetupMagazine;

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	                    const FAnimNotifyEventReference& EventReference) override;
};
