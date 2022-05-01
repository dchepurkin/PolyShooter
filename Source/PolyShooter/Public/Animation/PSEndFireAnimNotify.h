// PolyShooter By DChepurkin

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "PSEndFireAnimNotify.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnFireFinishedSignature, USkeletalMeshComponent*)

UCLASS()
class POLYSHOOTER_API UPSEndFireAnimNotify : public UAnimNotify
{
	GENERATED_BODY()

public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

	FOnFireFinishedSignature OnFireFinished;
	
};
