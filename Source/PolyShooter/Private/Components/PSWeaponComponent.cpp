// PolyShooter By DChepurkin

#include "Components/PSWeaponComponent.h"

#include "PSCharacterBase.h"
#include "PSEndEquipAnimNotify.h"
#include "PSEndReloadAnimNotify.h"
#include "PSWeaponBase.h"
#include "PSUtils.h"

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
	if(!NewWeapon) return;

	Weapons.AddUnique(NewWeapon);
}

void UPSWeaponComponent::SpawnWeapons()
{
	for(const auto WeaponClass : WeaponsClasses)
	{
		SpawnNewWeapon(WeaponClass);
	}
}

void UPSWeaponComponent::SpawnNewWeapon(TSubclassOf<APSWeaponBase> WeaponClass)
{
	const auto CharacterBase = GetOwner<APSCharacterBase>();
	if(!GetWorld() || !CharacterBase || !CharacterBase->GetMainMesh()) return;

	const auto Weapon = GetWorld()->SpawnActor<APSWeaponBase>(WeaponClass);
	if(!Weapon) return;

	const FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);

	Weapon->AttachToComponent(CharacterBase->GetMainMesh(), AttachmentRules, Weapon->GetWeaponData().AttachSocketName);
	Weapon->SetOwner(CharacterBase);

	Weapon->OnClipEmpty.AddUObject(this, &UPSWeaponComponent::OnClipEmpty);

	const auto EquipFinishedNotify = PSUtils::FindFirstNotify<UPSEndEquipAnimNotify>(
		Weapon->GetWeaponAnimData().EquipAnimMontage);
	if(EquipFinishedNotify) EquipFinishedNotify->OnEquipFinished.AddUObject(this, &UPSWeaponComponent::OnEquipFinished);

	const auto ReloadFinishedNotify = PSUtils::FindFirstNotify<UPSEndReloadAnimNotify>(
		Weapon->GetWeaponAnimData().ReloadAnimMontage);
	if(ReloadFinishedNotify)
		ReloadFinishedNotify->OnReloadFinished.AddUObject(
			this, &UPSWeaponComponent::OnReloadFinished);

	AddWeapon(Weapon);
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
	if(!CurrentWeapon) return false;

	CurrentWeapon->SetVisibility(true);

	return true;
}

void UPSWeaponComponent::EquipWeapon(int32 WeaponIndex)
{
	if(!CanEquip() || !SetCurrentWeapon(WeaponIndex)) return;

	IsEquiping = true;
	PSUtils::PlayMontage(GetOwner(), CurrentWeapon->GetWeaponAnimData().EquipAnimMontage);
}

bool UPSWeaponComponent::CanEquip()
{
	const auto Character = GetOwner<APSCharacterBase>();

	return CurrentWeapon && !IsEquiping && !IsReloading && Character && !Character->IsRunning() &&
		!CurrentWeapon->IsFire();
}

void UPSWeaponComponent::OnEquipFinished(USkeletalMeshComponent* MeshComponent)
{
	if(GetOwner<APSCharacterBase>() && GetOwner<APSCharacterBase>()->GetMainMesh() == MeshComponent)
	{
		IsEquiping = false;
	}
}

void UPSWeaponComponent::OnReloadFinished(USkeletalMeshComponent* MeshComponent)
{
	if(GetOwner<APSCharacterBase>() && GetOwner<APSCharacterBase>()->GetMainMesh() == MeshComponent)
	{
		IsReloading = false;
	}
}

void UPSWeaponComponent::StartFire()
{
	if(!CanFire()) return;

	CurrentWeapon->StartFire();
}

void UPSWeaponComponent::StopFire()
{
	if(!CurrentWeapon) return;

	CurrentWeapon->StopFire();
}

bool UPSWeaponComponent::CanFire()
{
	return CurrentWeapon && !IsEquiping && !IsReloading;
}

void UPSWeaponComponent::OnClipEmpty(APSWeaponBase* EmptyWeapon)
{
	if(!EmptyWeapon) return;
	if(CurrentWeapon != EmptyWeapon) EmptyWeapon->ChangeClip();

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

bool UPSWeaponComponent::CanReload()
{
	return CurrentWeapon && !IsEquiping && !IsReloading && CurrentWeapon->CanReload();
}

void UPSWeaponComponent::GetAmmoData(FAmmoData& AmmoData) const
{
	if(!CurrentWeapon) return;
	AmmoData = CurrentWeapon->GetAmmoData();
}

void UPSWeaponComponent::GetAnimData(FWeaponAnimData& AnimData) const
{
	if(!CurrentWeapon) return;
	AnimData = CurrentWeapon->GetWeaponAnimData();
}
