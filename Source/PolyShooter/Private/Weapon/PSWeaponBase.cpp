// PolyShooter By DChepurkin

#include "Weapon/PSWeaponBase.h"
#include "PSMagazineBase.h"
#include "PSUtils.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

DEFINE_LOG_CATEGORY_STATIC(LogPSWeaponBase, All, All)

APSWeaponBase::APSWeaponBase()
{
	PrimaryActorTick.bCanEverTick = false;

	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>("BaseMesh");
	WeaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	WeaponMesh->SetCastShadow(false);
	WeaponMesh->bOnlyOwnerSee = true;
	SetRootComponent(WeaponMesh);

	MagazineMesh = CreateDefaultSubobject<UStaticMeshComponent>("MagazineMesh");
	MagazineMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	MagazineMesh->SetCastShadow(false);
	MagazineMesh->bOnlyOwnerSee = true;
	MagazineMesh->SetupAttachment(WeaponMesh);
}

void APSWeaponBase::BeginPlay()
{
	Super::BeginPlay();

	check(WeaponMesh);
	check(MagazineMesh);

	SetVisibility(false);
	SetInfinite(DefaultAmmoData.IsInfinite);
}

void APSWeaponBase::OnEndFireAnim()
{
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

void APSWeaponBase::SetVisibility(bool Visible)
{
	if(WeaponMesh) WeaponMesh->SetVisibility(Visible, true);
}

void APSWeaponBase::StartFire()
{
	FireInProgress = true;
}

void APSWeaponBase::StopFire()
{
	FireInProgress = false;
}

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

	const auto Controller = Pawn->GetController();
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

void APSWeaponBase::MakeTrace(FHitResult& HitResult, const FVector& StartTrace, const FVector& EndTrace)
{
	if(!GetWorld() || !GetOwner()) return;

	FCollisionQueryParams CollisionQueryParams;
	CollisionQueryParams.AddIgnoredActor(GetOwner());
	CollisionQueryParams.bReturnPhysicalMaterial = true;

	GetWorld()->LineTraceSingleByChannel(HitResult, StartTrace, EndTrace, ECC_Visibility, CollisionQueryParams);
}

void APSWeaponBase::MakeShot()
{
	DecreaseAmmo();
	PSUtils::PlayMontage(GetOwner(), WeaponAnimData.FireAnimMontage);
	PSUtils::PlayCameraShake(GetOwner<APawn>(), WeaponData.FireCameraShake);
	UGameplayStatics::SpawnSoundAttached(WeaponSoundData.FireSoundCue, WeaponMesh);
	UGameplayStatics::SpawnEmitterAttached(MuzzleVFX, WeaponMesh, WeaponData.MuzzleSocketName,
	                                       FVector::ZeroVector,
	                                       FRotator::ZeroRotator);
}

void APSWeaponBase::DecreaseAmmo()
{
	if(AmmoData.Bullets) --AmmoData.Bullets;
}

void APSWeaponBase::SetInfinite(bool Infinite)
{
	AmmoData.IsInfinite = Infinite;
}

void APSWeaponBase::ChangeClip()
{
	AmmoData.Bullets = DefaultAmmoData.Bullets;
	if(!AmmoData.IsInfinite) --AmmoData.Clips;
}

bool APSWeaponBase::CanReload()
{
	return !IsFire() && AmmoData.Bullets < DefaultAmmoData.Bullets && (AmmoData.Clips || AmmoData.IsInfinite);
}

bool APSWeaponBase::CanFire()
{
	return !IsClipEmpty() && !IsFire();
}

void APSWeaponBase::SetMagazineVisible(bool Visibility)
{
	if(MagazineMesh) MagazineMesh->SetVisibility(Visibility);
}

UStaticMesh* APSWeaponBase::GetMagazineMesh()
{
	return MagazineMesh->GetStaticMesh().Get();
}

void APSWeaponBase::StartSetupMagazine()
{
	SpawnMagazine(WeaponData.MagazineInSocketName);
}

void APSWeaponBase::EndSetupMagazine()
{
	Magazine->Destroy();
	Magazine = nullptr;

	SetMagazineVisible(true);
}

void APSWeaponBase::StartReload()
{
	SetMagazineVisible(false);
}

void APSWeaponBase::SpawnMagazine(const FName& SocketName)
{
	const auto Character = GetOwner<APSCharacterBase>();
	if(!GetWorld() || !Character || !Character->GetMainMesh()) return;

	if(!Magazine) Magazine = GetWorld()->SpawnActor<APSMagazineBase>(APSMagazineBase::StaticClass());
	if(!Magazine) return;

	Magazine->SetOwner(Character);
	Magazine->SetMesh(GetMagazineMesh());

	const FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
	Magazine->AttachToComponent(Character->GetMainMesh(), AttachmentRules, SocketName);
}

void APSWeaponBase::AddClips(int32 ClipsAmount)
{
	if(!AmmoData.IsInfinite) AmmoData.Clips += ClipsAmount;
}
