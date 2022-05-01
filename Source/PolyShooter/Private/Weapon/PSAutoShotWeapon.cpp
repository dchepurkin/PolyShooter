// PolyShooter By DChepurkin

#include "Weapon/PSAutoShotWeapon.h"

void APSAutoShotWeapon::StartFire()
{
	if(!CanFire()) return;	
	
	GetWorldTimerManager().SetTimer(FireTimer, this, &APSAutoShotWeapon::MakeShot, FireRate, true);
	MakeShot();
	
	Super::StartFire();
}

void APSAutoShotWeapon::StopFire()
{
	GetWorldTimerManager().ClearTimer(FireTimer);
}
