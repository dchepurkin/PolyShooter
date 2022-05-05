// PolyShooter By DChepurkin

#include "Components/PSWeaponComponent.h"

#include "PSEndEquipAnimNotify.h"
#include "PSEndReloadAnimNotify.h"
#include "PSEndSetupMagazineAnimNotify.h"
#include "PSCharacterBase.h"
#include "PSMagazineBase.h"
#include "PSMagazineOutAnimNotify.h"
#include "PSStartSetupMagazineAnimNotify.h"
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
	if(!NewWeapon) return;

	Weapons.AddUnique(NewWeapon);
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
	SpawnNewWeapon(WeaponClass);
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

	const auto EquipFinishedNotify = PSUtils::FindFirstNotify<UPSEndEquipAnimNotify>(Weapon->GetWeaponAnimData().EquipAnimMontage);
	if(EquipFinishedNotify) EquipFinishedNotify->OnEquipFinished.AddUObject(this, &UPSWeaponComponent::OnEquipFinished);

	const auto ReloadFinishedNotify = PSUtils::FindFirstNotify<UPSEndReloadAnimNotify>(Weapon->GetWeaponAnimData().ReloadAnimMontage);
	if(ReloadFinishedNotify) ReloadFinishedNotify->OnReloadFinished.AddUObject(this, &UPSWeaponComponent::OnReloadFinished);

	const auto StartSetupMagazineNotify = PSUtils::FindFirstNotify<UPSStartSetupMagazineAnimNotify>(Weapon->GetWeaponAnimData().ReloadAnimMontage);
	if(StartSetupMagazineNotify) StartSetupMagazineNotify->OnStartSetupMagazine.AddUObject(this, &UPSWeaponComponent::OnStartSetupMagazine);

	const auto EndSetupMagazineNotify = PSUtils::FindFirstNotify<UPSEndSetupMagazineAnimNotify>(Weapon->GetWeaponAnimData().ReloadAnimMontage);
	if(EndSetupMagazineNotify) EndSetupMagazineNotify->OnEndSetupMagazine.AddUObject(this, &UPSWeaponComponent::OnEndSetupMagazine);

	const auto OutMagazineNotify = PSUtils::FindFirstNotify<UPSMagazineOutAnimNotify>(Weapon->GetWeaponAnimData().ReloadAnimMontage);
	if(OutMagazineNotify) OutMagazineNotify->OnMagazineOut.AddUObject(this, &UPSWeaponComponent::OnOutMagazine);

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
	UGameplayStatics::SpawnSoundAttached(CurrentWeapon->GetSoundData().AimInSoundCue, CurrentWeapon->GetWeaponMesh());
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
		IsEquiping = false;
}

void UPSWeaponComponent::OnReloadFinished(USkeletalMeshComponent* MeshComponent)
{
	if(GetOwner<APSCharacterBase>() && GetOwner<APSCharacterBase>()->GetMainMesh() == MeshComponent)
		IsReloading = false;
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

void UPSWeaponComponent::OnStartSetupMagazine(USkeletalMeshComponent* MeshComponent)
{
	const auto Character = GetOwner<APSCharacterBase>();
	if(!CurrentWeapon || !Character || Character->GetMainMesh() != MeshComponent) return;

	CurrentWeapon->StartSetupMagazine();
}

void UPSWeaponComponent::OnEndSetupMagazine(USkeletalMeshComponent* MeshComponent)
{
	const auto Character = GetOwner<APSCharacterBase>();
	if(!CurrentWeapon || !Character || Character->GetMainMesh() != MeshComponent) return;

	CurrentWeapon->EndSetupMagazine();
}

void UPSWeaponComponent::OnOutMagazine(USkeletalMeshComponent* MeshComponent)
{
	const auto Character = GetOwner<APSCharacterBase>();
	if(!CurrentWeapon || !Character || Character->GetMainMesh() != MeshComponent) return;

	CurrentWeapon->OutMagazine();
}
