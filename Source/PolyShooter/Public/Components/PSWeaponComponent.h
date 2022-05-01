// PolyShooter By DChepurkin

#pragma once

#include "CoreMinimal.h"
#include "PSCoreTypes.h"
#include "Components/ActorComponent.h"
#include "PSWeaponComponent.generated.h"

class APSWeaponBase;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class POLYSHOOTER_API UPSWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPSWeaponComponent();

	void AddWeapon(APSWeaponBase* NewWeapon);
	void EquipWeapon(int32 WeaponIndex);

	UFUNCTION(BlueprintCallable)
	void GetAmmoData(FAmmoData& AmmoData) const;
	void GetAnimData(FWeaponAnimData& AnimData) const;

	void StartFire();
	void StopFire();
	void ChangeClip();

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=PSWeaponComponent)
	TArray<TSubclassOf<APSWeaponBase>> WeaponsClasses;

private:
	TArray<APSWeaponBase*> Weapons;
	bool IsEquiping = false;
	bool IsReloading = false;

	UPROPERTY()
	APSWeaponBase* CurrentWeapon;

	void SpawnWeapons();
	void SpawnNewWeapon(TSubclassOf<APSWeaponBase> WeaponClass);

	void OnEquipFinished(USkeletalMeshComponent* MeshComponent);
	void OnReloadFinished(USkeletalMeshComponent* MeshComponent);
	void OnClipEmpty(APSWeaponBase* EmptyWeapon);	

	bool SetCurrentWeapon(int32 WeaponIndex);
	bool CanEquip();
	bool CanFire();
	bool CanReload();
};
