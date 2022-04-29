// PolyShooter By DChepurkin

#include "Components/PSWeaponComponent.h"

#include "PSCharacterBase.h"
#include "PSEndEquipAnimNotify.h"
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

	const auto Notify = PSUtils::FindFirstNotify<UPSEndEquipAnimNotify>(Weapon->GetWeaponAnimData().EquipAnimMontage);
	if(Notify) Notify->OnEquipFinished.AddUObject(this, &UPSWeaponComponent::OnEquipFinished);

	AddWeapon(Weapon);
}

bool UPSWeaponComponent::SetCurrentWeapon(int32 WeaponIndex)
{
	if(Weapons.IsEmpty() || WeaponIndex > Weapons.Num() - 1) return false;

	if(CurrentWeapon) CurrentWeapon->SetVisibility(false);

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

	return !IsEquiping && Character && !Character->IsRunning();
}

void UPSWeaponComponent::OnEquipFinished(USkeletalMeshComponent* MeshComponent)
{
	if(GetOwner<APSCharacterBase>() && GetOwner<APSCharacterBase>()->GetMainMesh() == MeshComponent)
	{
		IsEquiping = false;
	}
}
