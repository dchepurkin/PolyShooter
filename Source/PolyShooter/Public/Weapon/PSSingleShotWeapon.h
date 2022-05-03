// PolyShooter By DChepurkin

#pragma once

#include "CoreMinimal.h"
#include "Weapon/PSBulletWeapon.h"
#include "PSSingleShotWeapon.generated.h"

UCLASS()
class POLYSHOOTER_API APSSingleShotWeapon : public APSBulletWeapon
{
	GENERATED_BODY()

public:
	virtual bool IsFire() override { return FireInProgress; }

protected:
	virtual void StartFire() override;
	virtual void StopFire() override {};
	virtual void OnFireAnimFinished(USkeletalMeshComponent* MeshComponent) override;
};
