// PolyShooter By DChepurkin

#include "Weapon/PSWeaponBase.h"

APSWeaponBase::APSWeaponBase()
{
	PrimaryActorTick.bCanEverTick = false;

	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>("BaseMesh");
	WeaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	WeaponMesh->SetCastShadow(false);
	WeaponMesh->bOnlyOwnerSee = true;

	SetRootComponent(WeaponMesh);
}

void APSWeaponBase::BeginPlay()
{
	Super::BeginPlay();

	check(WeaponMesh);

	SetVisibility(false);
}

void APSWeaponBase::SetVisibility(bool Visible) const
{
	if(!WeaponMesh) return;

	WeaponMesh->SetVisibility(Visible, true);
}
