// PolyShooter By DChepurkin

#include "Pickup/PSAmmoBoxPickup.h"

#include "PSWeaponBase.h"
#include "PSWeaponComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogPSAmmoPickup, All, All);

void APSAmmoBoxPickup::BeginPlay()
{
	Super::BeginPlay();
	
	if(Weapons.IsEmpty()) Destroy();
}

void APSAmmoBoxPickup::AddWeapon(TSubclassOf<APSWeaponBase> WeaponClass, int32 ClipsAmount)
{
	Weapons.Add(WeaponClass, ClipsAmount);
}

void APSAmmoBoxPickup::TakePickup(AActor* OtherActor)
{
	const auto WeaponComponent = OtherActor->FindComponentByClass<UPSWeaponComponent>();
	if(!WeaponComponent) return;

	for(const auto& Weapon : Weapons)
	{
		WeaponComponent->AddClips(Weapon.Key, Weapon.Value);
	}

	Super::TakePickup(OtherActor);
}
