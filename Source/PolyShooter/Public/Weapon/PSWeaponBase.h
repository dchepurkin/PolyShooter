// PolyShooter By DChepurkin

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PSCoreTypes.h"
#include "PSWeaponBase.generated.h"

class UStaticMeshComponent;
class APSWeaponBase;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnClipEmptySignature, APSWeaponBase*)

UCLASS()
class POLYSHOOTER_API APSWeaponBase : public AActor
{
	GENERATED_BODY()

public:
	APSWeaponBase();

	FOnClipEmptySignature OnClipEmpty;

	const FWeaponAnimData& GetWeaponAnimData() const { return WeaponAnimData; }
	const FWeaponData& GetWeaponData() const { return WeaponData; }
	const FAmmoData& GetAmmoData() const { return AmmoData; }

	virtual void StartFire();
	virtual void StopFire();
	virtual bool IsFire() { return false; }

	bool IsAmmoEmpty();
	bool IsClipEmpty();
	bool CanReload();

	void SetVisibility(bool Visible) const;
	void ChangeClip();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=PSWeaponBase)
	UStaticMeshComponent* WeaponMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=PSWeaponBase, meta=(ClampMin = "0.0"))
	float Damage = 10.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=PSWeaponBase, meta=(ClampMin = "0.0"))
	float FireDistance = 1500.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=PSWeaponBase, meta=(ClampMin = "0.0"))
	float BulletSpread = 1.5f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=PSWeaponBase)
	FWeaponData WeaponData;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=PSWeaponBase)
	FAmmoData DefaultAmmoData;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=PSWeaponBase)
	FWeaponAnimData WeaponAnimData;

	bool CanFire();
	bool GetTraceData(FVector& StartTrace, FVector& EndTrace);
	void FireLineTrace(FHitResult& HitResult, const FVector& StartTrace, const FVector& EndTrace);

	virtual void MakeShot();
	virtual void OnFireAnimFinished(USkeletalMeshComponent* MeshComponent);

private:
	FAmmoData AmmoData;

	bool GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation);
	void GetMuzzleSocketTransform(FVector& ViewLocation, FRotator& ViewRotation);
	void DecreaseAmmo();
};
