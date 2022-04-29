// PolyShooter By DChepurkin

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PSCoreTypes.h"
#include "PSWeaponBase.generated.h"

class UStaticMeshComponent;

UCLASS()
class POLYSHOOTER_API APSWeaponBase : public AActor
{
	GENERATED_BODY()

public:
	APSWeaponBase();

	const FWeaponAnimData& GetWeaponAnimData() const { return WeaponAnimData; }
	const FWeaponData& GetWeaponData() const { return WeaponData; }
	void SetVisibility(bool Visible) const;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=PSWeaponBase)
	UStaticMeshComponent* WeaponMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=PSWeaponBase, meta=(ClampMin = "0.0"))
	float Damage = 10.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=PSWeaponBase, meta=(ClampMin = "0.0"))
	float FireDistance = 1500.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=PSWeaponBase, meta=(ClampMin = "0.01"))
	float FireRate = 0.1f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=PSWeaponBase)
	FWeaponData WeaponData;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=PSWeaponBase)
	FAmmoData AmmoData;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=PSWeaponBase)
	FWeaponAnimData WeaponAnimData;
};
