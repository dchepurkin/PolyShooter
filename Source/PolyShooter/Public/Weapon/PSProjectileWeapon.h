// PolyShooter By DChepurkin

#pragma once

#include "CoreMinimal.h"
#include "Weapon/PSWeaponBase.h"
#include "PSProjectileWeapon.generated.h"

class APSProjectileBase;

UCLASS()
class POLYSHOOTER_API APSProjectileWeapon : public APSWeaponBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=PSWeaponBase)
	TSubclassOf<APSProjectileBase> ProjectileClass;
};
