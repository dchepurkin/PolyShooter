// PolyShooter By DChepurkin

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "PSEndReloadAnimNotify.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnReloadFinishedSugnature, USkeletalMeshComponent*)

UCLASS()
class POLYSHOOTER_API UPSEndReloadAnimNotify : public UAnimNotify
{
	GENERATED_BODY()

public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	                    const FAnimNotifyEventReference& EventReference) override;

	FOnReloadFinishedSugnature OnReloadFinished;
};
