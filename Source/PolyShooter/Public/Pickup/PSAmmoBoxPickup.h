// PolyShooter By DChepurkin

#pragma once

#include "CoreMinimal.h"
#include "Pickup/PSPickupBase.h"
#include "PSAmmoBoxPickup.generated.h"

class APSWeaponBase;

UCLASS()
class POLYSHOOTER_API APSAmmoBoxPickup : public APSPickupBase
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	void AddWeapon(TSubclassOf<APSWeaponBase> WeaponClass, int32 ClipsAmount);

protected:
	TMap<TSubclassOf<APSWeaponBase>, int32> Weapons;

	virtual void TakePickup(AActor* OtherActor) override;
};
