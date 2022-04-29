// PolyShooter By DChepurkin

#pragma once

#include "CoreMinimal.h"
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
	UFUNCTION(BlueprintCallable)
	void EquipWeapon(int32 WeaponIndex);
	APSWeaponBase* GetCurrentWeapon() const { return CurrentWeapon; }

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=PSWeaponComponent)
	TArray<TSubclassOf<APSWeaponBase>> WeaponsClasses;

private:
	TArray<APSWeaponBase*> Weapons;
	bool IsEquiping = false;

	UPROPERTY()
	APSWeaponBase* CurrentWeapon;

	void SpawnWeapons();
	void SpawnNewWeapon(TSubclassOf<APSWeaponBase> WeaponClass);	
	
	void OnEquipFinished(USkeletalMeshComponent* MeshComponent);

	bool SetCurrentWeapon(int32 WeaponIndex);
	bool CanEquip();
};
