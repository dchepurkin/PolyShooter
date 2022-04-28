// PolyShooter By DChepurkin


#include "Weapon/PSWeaponBase.h"

APSWeaponBase::APSWeaponBase()
{
	PrimaryActorTick.bCanEverTick = false;

	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>("BaseMesh");
	SetRootComponent(WeaponMesh);
}

void APSWeaponBase::BeginPlay()
{
	Super::BeginPlay();

	check(WeaponMesh);
}

