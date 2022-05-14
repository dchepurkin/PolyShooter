// PolyShooter By DChepurkin

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "PSAnimNotifyStateBase.generated.h"

class UPSWeaponComponent;

UCLASS()
class POLYSHOOTER_API UPSAnimNotifyStateBase : public UAnimNotifyState
{
	GENERATED_BODY()

public:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration,
	                         const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
	
protected:
	virtual void OnNotifyBegin(UPSWeaponComponent* WeaponComponent) {}
	virtual void OnNotifyEnd(UPSWeaponComponent* WeaponComponent) {}

private:
	void Begin(const USkeletalMeshComponent* MeshComp);
	void End(const USkeletalMeshComponent* MeshComp);

	UPSWeaponComponent* GetWeaponComponent(const USkeletalMeshComponent* MeshComp);
};
