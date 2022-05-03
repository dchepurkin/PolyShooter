// PolyShooter By DChepurkin

#include "Weapon/PSAutoShotWeapon.h"

#include "PSMagazineBase.h"

void APSAutoShotWeapon::StartFire()
{
	if(!CanFire()) return;

	GetWorldTimerManager().SetTimer(FireTimer, this, &APSAutoShotWeapon::MakeShot, FireRate, true);
	MakeShot();

	Super::StartFire();
}

void APSAutoShotWeapon::StopFire()
{
	Super::StopFire();
	GetWorldTimerManager().ClearTimer(FireTimer);
}

void APSAutoShotWeapon::OutMagazine()
{
	Super::OutMagazine();
	SpawnMagazine(WeaponData.MagazineOutSocketName);
}
