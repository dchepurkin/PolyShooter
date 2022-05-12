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

	UFUNCTION(BlueprintCallable)
	void GetAmmoData(FAmmoData& AmmoData) const;
	void GetAnimData(FWeaponAnimData& AnimData) const;
	void GetUIData(FWeaponUIData& WeaponUIData) const;

	void StartFire();
	void StopFire();
	void ChangeClip();

	void SpawnAmmoBox();

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=PSWeaponComponent)
	TMap<TSubclassOf<APSWeaponBase>, int32> WeaponsStruct;

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

	void OnEquipFinished(USkeletalMeshComponent* MeshComponent);
	void OnReloadFinished(USkeletalMeshComponent* MeshComponent);
	void OnStartSetupMagazine(USkeletalMeshComponent* MeshComponent);
	void OnEndSetupMagazine(USkeletalMeshComponent* MeshComponent);
	void OnOutMagazine(USkeletalMeshComponent* MeshComponent);
	void OnClipEmpty(APSWeaponBase* EmptyWeapon);

	bool SetCurrentWeapon(int32 WeaponIndex);
	bool CanEquip();
	bool CanFire();
	bool CanReload();
};
