// PolyShooter By DChepurkin

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "PSEndEquipAnimNotify.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnEquipFinishedSignature, USkeletalMeshComponent*)

UCLASS()
class POLYSHOOTER_API UPSEndEquipAnimNotify : public UAnimNotify
{
	GENERATED_BODY()

public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	                    const FAnimNotifyEventReference& EventReference) override;

	FOnEquipFinishedSignature OnEquipFinished;
	
};
