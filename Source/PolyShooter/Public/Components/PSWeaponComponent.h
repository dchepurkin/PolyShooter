// PolyShooter By DChepurkin

#pragma once

#include "CoreMinimal.h"
#include "PSCoreTypes.h"
#include "Components/ActorComponent.h"
#include "PSWeaponComponent.generated.h"

class APSWeaponBase;
class APSAmmoBoxPickup;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnSetCurrentWeaponSignature, APSWeaponBase* CurrentWeapon);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class POLYSHOOTER_API UPSWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPSWeaponComponent();

	FOnSetCurrentWeaponSignature OnChangeWeapon;

	void AddWeapon(APSWeaponBase* NewWeapon);
	void AddClips(TSubclassOf<APSWeaponBase> WeaponClass, int32 ClipsAmount);
	void EquipWeapon(int32 WeaponIndex);

	void GetAmmoData(FAmmoData& AmmoData) const;
	void GetAnimData(FWeaponAnimData& AnimData) const;
	void GetUIData(FWeaponUIData& WeaponUIData) const;

	void StartFire();
	void StopFire();
	void ChangeClip();

	void SpawnAmmoBox();

	void OnEquipFinished() { IsEquiping = false; }
	void OnReloadFinished() { IsReloading = false; }
	void OnReloadStarted();
	void OnStartSetupMagazine();
	void OnEndSetupMagazine();
	void OnEndFireAnim();

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=PSWeaponComponent)
	TMap<TSubclassOf<APSWeaponBase>, int32> StartWeapons;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=PSWeaponComponent)
	TSubclassOf<APSAmmoBoxPickup> AmmoBoxPickupClass;

private:
	TArray<APSWeaponBase*> Weapons;
	bool IsEquiping = false;
	bool IsReloading = false;

	UPROPERTY()
	APSWeaponBase* CurrentWeapon;

	void SpawnWeapons();
	void SpawnNewWeapon(TSubclassOf<APSWeaponBase> WeaponClass, int32 ClipsAmount);

	void OnClipEmpty(APSWeaponBase* EmptyWeapon);

	bool SetCurrentWeapon(int32 WeaponIndex);
	bool CanEquip();
	bool CanFire();
	bool CanReload();
};
