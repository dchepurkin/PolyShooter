// PolyShooter By DChepurkin

#include "Components/PSWeaponComponent.h"

#include "PSAmmoBoxPickup.h"
#include "PSCharacterBase.h"
#include "PSMagazineBase.h"
#include "PSWeaponBase.h"
#include "PSUtils.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

DEFINE_LOG_CATEGORY_STATIC(LogPSWeaponComponent, All, All)

UPSWeaponComponent::UPSWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UPSWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	SpawnWeapons();
	SetCurrentWeapon(0);
}

void UPSWeaponComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	CurrentWeapon = nullptr;
	for(const auto Weapon : Weapons)
	{
		Weapon->DetachFromActor(FDetachmentTransformRules::KeepRelativeTransform);
		Weapon->Destroy();
	}
	Weapons.Empty();
	Super::EndPlay(EndPlayReason);
}

void UPSWeaponComponent::AddWeapon(APSWeaponBase* NewWeapon)
{
	if(NewWeapon) Weapons.AddUnique(NewWeapon);
}

void UPSWeaponComponent::AddClips(TSubclassOf<APSWeaponBase> WeaponClass, int32 ClipsAmount)
{
	for(const auto Weapon : Weapons)
	{
		if(Weapon->IsA(WeaponClass))
		{
			Weapon->AddClips(ClipsAmount);
			if(Weapon->IsClipEmpty()) OnClipEmpty(Weapon);
			return;
		}
	}
	SpawnNewWeapon(WeaponClass, ClipsAmount);
}

void UPSWeaponComponent::SpawnWeapons()
{
	for(const auto& StartWeapon : StartWeapons)
	{
		SpawnNewWeapon(StartWeapon.Key, StartWeapon.Value);
	}
}

void UPSWeaponComponent::SpawnNewWeapon(TSubclassOf<APSWeaponBase> WeaponClass, int32 ClipsAmount)
{
	const auto CharacterBase = GetOwner<APSCharacterBase>();
	if(!GetWorld() || !CharacterBase || !CharacterBase->GetMainMesh()) return;

	const auto Weapon = GetWorld()->SpawnActor<APSWeaponBase>(WeaponClass);
	if(!Weapon) return;

	const FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
	Weapon->AttachToComponent(CharacterBase->GetMainMesh(), AttachmentRules, Weapon->GetWeaponData().AttachSocketName);
	Weapon->SetOwner(CharacterBase);
	Weapon->OnClipEmpty.AddUObject(this, &UPSWeaponComponent::OnClipEmpty);

	AddWeapon(Weapon);
	AddClips(WeaponClass, ClipsAmount);
}

bool UPSWeaponComponent::SetCurrentWeapon(int32 WeaponIndex)
{
	if(Weapons.IsEmpty() ||
		WeaponIndex > Weapons.Num() - 1 ||
		CurrentWeapon == Weapons[WeaponIndex])
		return false;

	if(CurrentWeapon)
	{
		StopFire();
		CurrentWeapon->SetVisibility(false);
	}

	CurrentWeapon = Weapons[WeaponIndex];
	CurrentWeapon->SetVisibility(true);

	OnChangeWeapon.Broadcast(CurrentWeapon);
	return true;
}

void UPSWeaponComponent::EquipWeapon(int32 WeaponIndex)
{
	if(!CanEquip() || !SetCurrentWeapon(WeaponIndex)) return;

	IsEquiping = true;
	PSUtils::PlayMontage(GetOwner(), CurrentWeapon->GetWeaponAnimData().EquipAnimMontage);
	UGameplayStatics::SpawnSoundAttached(CurrentWeapon->GetSoundData().AimInSoundCue, CurrentWeapon->GetWeaponMesh());
}

bool UPSWeaponComponent::CanEquip()
{
	const auto Character = GetOwner<APSCharacterBase>();

	return CurrentWeapon
		&& !IsEquiping
		&& !IsReloading
		&& Character
		&& !Character->IsRunning()
		&& !CurrentWeapon->IsFire();
}

void UPSWeaponComponent::OnStartSetupMagazine()
{
	if(CurrentWeapon) CurrentWeapon->StartSetupMagazine();
}

void UPSWeaponComponent::OnEndSetupMagazine()
{
	if(CurrentWeapon) CurrentWeapon->EndSetupMagazine();
}

void UPSWeaponComponent::OnEndFireAnim()
{
	if(CurrentWeapon) CurrentWeapon->OnEndFireAnim();
}

void UPSWeaponComponent::OnReloadStarted()
{
	if(CurrentWeapon) CurrentWeapon->StartReload();
}

void UPSWeaponComponent::StartFire()
{
	if(CanFire()) CurrentWeapon->StartFire();
}

void UPSWeaponComponent::StopFire()
{
	if(CurrentWeapon) CurrentWeapon->StopFire();
}

bool UPSWeaponComponent::CanFire()
{
	return CurrentWeapon
		&& !IsEquiping
		&& !IsReloading;
}

bool UPSWeaponComponent::CanReload()
{
	return CurrentWeapon
		&& !IsEquiping
		&& !IsReloading
		&& CurrentWeapon->CanReload();
}

void UPSWeaponComponent::OnClipEmpty(APSWeaponBase* EmptyWeapon)
{
	if(!EmptyWeapon) return;
	if(CurrentWeapon != EmptyWeapon)
	{
		EmptyWeapon->ChangeClip();
		return;
	}

	StopFire();
	ChangeClip();
}

void UPSWeaponComponent::ChangeClip()
{
	if(!CanReload()) return;

	IsReloading = true;
	PSUtils::PlayMontage(GetOwner(), CurrentWeapon->GetWeaponAnimData().ReloadAnimMontage);
	CurrentWeapon->ChangeClip();
}

void UPSWeaponComponent::SpawnAmmoBox()
{
	if(!AmmoBoxPickupClass || !GetWorld() || !GetOwner()) return;

	const auto SpawnLocation = APSPickupBase::GetSpawnLocationSnapedToFloor(GetWorld(), GetOwner()->GetActorLocation());
	const FTransform SpawnTransform(SpawnLocation);
	const auto AmmoBox = GetWorld()->SpawnActorDeferred<APSAmmoBoxPickup>(AmmoBoxPickupClass, SpawnTransform);
	if(!AmmoBox) return;

	for(const auto Weapon : Weapons)
	{
		if(Weapon && !Weapon->GetAmmoData().IsInfinite && Weapon->GetAmmoData().Clips)
			AmmoBox->AddWeapon(Weapon->GetClass(), Weapon->GetAmmoData().Clips);
	}

	AmmoBox->FinishSpawning(SpawnTransform);
}

void UPSWeaponComponent::GetAmmoData(FAmmoData& AmmoData) const
{
	if(CurrentWeapon) AmmoData = CurrentWeapon->GetAmmoData();
}

void UPSWeaponComponent::GetAnimData(FWeaponAnimData& AnimData) const
{
	if(CurrentWeapon) AnimData = CurrentWeapon->GetWeaponAnimData();
}

void UPSWeaponComponent::GetUIData(FWeaponUIData& WeaponUIData) const
{
	if(CurrentWeapon) WeaponUIData = CurrentWeapon->GetWeaponUIData();
}
