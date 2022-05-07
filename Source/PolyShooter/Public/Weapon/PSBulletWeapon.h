// PolyShooter By DChepurkin

#pragma once

#include "CoreMinimal.h"
#include "Weapon/PSWeaponBase.h"
#include "PSBulletWeapon.generated.h"

class UPSWeaponFXComponent;

UCLASS()
class POLYSHOOTER_API APSBulletWeapon : public APSWeaponBase
{
	GENERATED_BODY()

public:
	APSBulletWeapon();

protected:

	virtual void MakeShot() override;
	void MakeDamage(const FHitResult& HitResult) const;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category=PSWeaponBase)
	UPSWeaponFXComponent* WeaponFxComponent;
};
