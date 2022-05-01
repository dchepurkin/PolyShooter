// PolyShooter By DChepurkin

#pragma once

#include "CoreMinimal.h"
#include "Weapon/PSWeaponBase.h"
#include "PSBulletWeapon.generated.h"

UCLASS()
class POLYSHOOTER_API APSBulletWeapon : public APSWeaponBase
{
	GENERATED_BODY()

protected:

	virtual void MakeShot() override;
	void MakeDamage(const FHitResult& HitResult) const;
};
