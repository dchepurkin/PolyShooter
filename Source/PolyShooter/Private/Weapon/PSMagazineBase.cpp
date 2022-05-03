// PolyShooter By DChepurkin

#include "Weapon/PSMagazineBase.h"

APSMagazineBase::APSMagazineBase()
{
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Mesh->SetCastShadow(false);
	Mesh->bOnlyOwnerSee = true;
	SetRootComponent(Mesh);
}

void APSMagazineBase::BeginPlay()
{
	Super::BeginPlay();
}

void APSMagazineBase::SetMesh(UStaticMesh* NewMesh)
{
	Mesh->SetStaticMesh(NewMesh);
}

void APSMagazineBase::SetPhysicsEnabled(bool Enabled)
{
	Mesh->SetCollisionEnabled(Enabled ? ECollisionEnabled::PhysicsOnly : ECollisionEnabled::NoCollision);
	Mesh->SetSimulatePhysics(Enabled);
}
