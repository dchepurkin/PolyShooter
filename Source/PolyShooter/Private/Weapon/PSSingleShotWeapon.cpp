// PolyShooter By DChepurkin

#include "Weapon/PSSingleShotWeapon.h"

void APSSingleShotWeapon::StartFire()
{
	if(!CanFire()) return;
	FireInProgress = true;
	MakeShot();

	Super::StartFire();
}

void APSSingleShotWeapon::OnFireAnimFinished(USkeletalMeshComponent* MeshComponent)
{
	Super::OnFireAnimFinished(MeshComponent);
	FireInProgress = false;
}
