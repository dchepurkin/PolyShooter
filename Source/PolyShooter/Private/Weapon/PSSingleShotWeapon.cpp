// PolyShooter By DChepurkin

#include "Weapon/PSSingleShotWeapon.h"

#include "PSMagazineBase.h"

void APSSingleShotWeapon::StartFire()
{
	if(!CanFire()) return;
	FireInProgress = true;
	MakeShot();

	Super::StartFire();
}

void APSSingleShotWeapon::OnFireAnimFinished(USkeletalMeshComponent* MeshComponent)
{
	FireInProgress = false;
	Super::OnFireAnimFinished(MeshComponent);	
}
