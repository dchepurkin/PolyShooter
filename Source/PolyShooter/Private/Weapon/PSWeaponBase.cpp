// PolyShooter By DChepurkin

#include "Weapon/PSWeaponBase.h"
#include "DrawDebugHelpers.h"
#include "PSEndFireAnimNotify.h"
#include "PSUtils.h"

DEFINE_LOG_CATEGORY_STATIC(LogPSWeaponBase, All, All)

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
	AmmoData = DefaultAmmoData;

	const auto FireEndNotify = PSUtils::FindFirstNotify<UPSEndFireAnimNotify>(WeaponAnimData.FireAnimMontage);
	if(FireEndNotify) FireEndNotify->OnFireFinished.AddUObject(this, &APSWeaponBase::OnFireAnimFinished);
}

void APSWeaponBase::OnFireAnimFinished(USkeletalMeshComponent* MeshComponent)
{
	const auto Character = GetOwner<APSCharacterBase>();
	if(!Character || Character->GetMainMesh() != MeshComponent) return;

	if(IsClipEmpty()) OnClipEmpty.Broadcast(this);
}

bool APSWeaponBase::IsClipEmpty()
{
	return !AmmoData.Bullets;
}

bool APSWeaponBase::IsAmmoEmpty()
{
	return IsClipEmpty() && !AmmoData.Clips;
}

void APSWeaponBase::SetVisibility(bool Visible) const
{
	if(!WeaponMesh) return;

	WeaponMesh->SetVisibility(Visible, true);
}

void APSWeaponBase::StartFire() {}

void APSWeaponBase::StopFire() {}

bool APSWeaponBase::GetTraceData(FVector& StartTrace, FVector& EndTrace)
{
	FVector ViewLocation;
	FRotator ViewRotation;

	if(!GetPlayerViewPoint(ViewLocation, ViewRotation)) return false;

	StartTrace = ViewLocation;
	const auto ShootDirection = FMath::VRandCone(ViewRotation.Vector(), FMath::DegreesToRadians(BulletSpread));
	EndTrace = ShootDirection * FireDistance + StartTrace;

	return true;
}

bool APSWeaponBase::GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation)
{
	const auto Pawn = GetOwner<APawn>();
	if(!Pawn) return false;

	const auto Controller = Pawn->GetController<APlayerController>();
	if(!Controller) return false;

	Controller->IsPlayerController()
		? Controller->GetPlayerViewPoint(ViewLocation, ViewRotation)
		: GetMuzzleSocketTransform(ViewLocation, ViewRotation);

	return true;
}

void APSWeaponBase::GetMuzzleSocketTransform(FVector& ViewLocation, FRotator& ViewRotation)
{
	ViewLocation = WeaponMesh->GetSocketLocation(WeaponData.MuzzleSocketName);
	ViewRotation = WeaponMesh->GetSocketRotation(WeaponData.MuzzleSocketName);
}

void APSWeaponBase::FireLineTrace(FHitResult& HitResult, const FVector& StartTrace, const FVector& EndTrace)
{
	if(!GetWorld() || !GetOwner()) return;

	FCollisionQueryParams CollisionQueryParams;
	CollisionQueryParams.AddIgnoredActor(GetOwner());
	CollisionQueryParams.bReturnPhysicalMaterial = true;

	GetWorld()->LineTraceSingleByChannel(HitResult, StartTrace, EndTrace, ECC_Visibility, CollisionQueryParams);
	if(HitResult.bBlockingHit)
	{
		DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 2.0f, 8, FColor::Green, false, 5.0f, 0, 1.0f);
	}
}

void APSWeaponBase::MakeShot()
{
	DecreaseAmmo();
	PSUtils::PlayMontage(GetOwner(), WeaponAnimData.FireAnimMontage);
}

void APSWeaponBase::DecreaseAmmo()
{
	if(AmmoData.Bullets)
		--AmmoData.Bullets;
}

void APSWeaponBase::ChangeClip()
{
	AmmoData.Bullets = DefaultAmmoData.Bullets;
	--AmmoData.Clips;
}

bool APSWeaponBase::CanReload()
{
	return AmmoData.Bullets < DefaultAmmoData.Bullets && AmmoData.Clips;
}

bool APSWeaponBase::CanFire()
{
	return !IsClipEmpty() && !IsFire();
}
