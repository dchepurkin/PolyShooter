// PolyShooter By DChepurkin

#pragma once

#include "CoreMinimal.h"
#include "PSWeaponBase.h"
#include "Pickup/PSPickupBase.h"
#include "PSAmmoPickup.generated.h"

UCLASS()
class POLYSHOOTER_API APSAmmoPickup : public APSPickupBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=PSPickup)
	TSubclassOf<APSWeaponBase> Weapon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=PSPickup)
	int32 ClipsAmount;

	virtual void TakePickup(AActor* OtherActor) override;
};
