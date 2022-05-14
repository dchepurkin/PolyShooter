// PolyShooter By DChepurkin

#include "Weapon/PSBulletWeapon.h"
#include "Kismet/GameplayStatics.h"
#include "PSWeaponFXComponent.h"

APSBulletWeapon::APSBulletWeapon()	
{
	WeaponFxComponent = CreateDefaultSubobject<UPSWeaponFXComponent>("WeaponFXComponent");
}

void APSBulletWeapon::MakeShot()
{
	FHitResult HitResult;
	FVector StartTrace;
	FVector EndTrace;

	if(GetTraceData(StartTrace, EndTrace))
		MakeTrace(HitResult, StartTrace, EndTrace);

	if(HitResult.bBlockingHit) { MakeDamage(HitResult); }

	Super::MakeShot();
}

void APSBulletWeapon::MakeDamage(const FHitResult& HitResult) const
{
	const auto DamagePawn = GetOwner<APawn>();
	if(!DamagePawn) return;

	const auto DamageController = DamagePawn->GetController();
	if(!DamageController) return;

	UGameplayStatics::ApplyDamage(HitResult.GetActor(), Damage, DamageController, DamagePawn, nullptr);

	if(!WeaponFxComponent) return;

	WeaponFxComponent->PlayImpactFX(HitResult);
}
