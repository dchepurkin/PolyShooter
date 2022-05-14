// PolyShooter By DChepurkin

#include "Weapon/PSProjectileWeapon.h"

#include "PSProjectileBase.h"

void APSProjectileWeapon::StartFire()
{
	SetMagazineVisible(false);
	MakeShot();
}

void APSProjectileWeapon::SetVisibility(bool Visible)
{
	Super::SetVisibility(Visible);
	MagazineMesh->SetVisibility(Visible && !IsAmmoEmpty());
}

void APSProjectileWeapon::MakeShot()
{
	if(!CanFire()) return;

	FHitResult HitResult;
	FVector StartTrace;
	FVector EndTrace;

	if(GetTraceData(StartTrace, EndTrace))
		MakeTrace(HitResult, StartTrace, EndTrace);

	const auto EndPoint = HitResult.bBlockingHit ? HitResult.ImpactPoint : EndTrace;
	const FVector Direction = (EndPoint - WeaponMesh->GetSocketLocation(WeaponData.MuzzleSocketName)).GetSafeNormal();

	FireInProgress = true;
	SpawnProjectile(Direction);
	Super::MakeShot();
}

void APSProjectileWeapon::OnEndFireAnim()
{
	FireInProgress = false;
	Super::OnEndFireAnim();
}

void APSProjectileWeapon::SpawnProjectile(const FVector& Direction)
{
	if(!GetWorld()) return;

	const auto Pawn = GetOwner<APawn>();
	if(!Pawn) return;

	const auto Projectile = GetWorld()->SpawnActorDeferred<APSProjectileBase>(
		ProjectileClass, WeaponMesh->GetSocketTransform(WeaponData.MuzzleSocketName), Pawn, Pawn);
	if(!Projectile) return;

	Projectile->SetOwner(Pawn);
	Projectile->SetDirection(Direction);
	Projectile->FinishSpawning(WeaponMesh->GetSocketTransform(WeaponData.MuzzleSocketName));
}
