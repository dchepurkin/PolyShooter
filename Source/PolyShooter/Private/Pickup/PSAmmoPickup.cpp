// PolyShooter By DChepurkin

#include "Pickup/PSAmmoPickup.h"

#include "PSWeaponComponent.h"

void APSAmmoPickup::TakePickup(AActor* OtherActor)
{
	const auto WeaponComponent = OtherActor->FindComponentByClass<UPSWeaponComponent>();
	if(!WeaponComponent) return;

	WeaponComponent->AddClips(Weapon, ClipsAmount);
	Super::TakePickup(OtherActor);
}
