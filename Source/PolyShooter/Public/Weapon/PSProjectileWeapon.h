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

public:
	virtual bool IsFire() override { return FireInProgress; }
	virtual void SetVisibility(bool Visible) override;
	virtual void OnEndFireAnim() override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=PSWeaponBase)
	TSubclassOf<APSProjectileBase> ProjectileClass;

	virtual void StartFire() override;
	virtual void MakeShot() override;	

private:
	bool FireInProgress = false;
	void SpawnProjectile(const FVector& Direction);
};
