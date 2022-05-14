// PolyShooter By DChepurkin

#pragma once

#include "CoreMinimal.h"
#include "Weapon/PSBulletWeapon.h"
#include "PSAutoShotWeapon.generated.h"

UCLASS()
class POLYSHOOTER_API APSAutoShotWeapon : public APSBulletWeapon
{
	GENERATED_BODY()
public:
	virtual void StartReload() override;
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=PSWeaponBase, meta=(ClampMin = "0.01"))
	float FireRate = 0.1f;
	
	virtual void StartFire() override;
	virtual void StopFire() override;

private:
	FTimerHandle FireTimer;	
};
