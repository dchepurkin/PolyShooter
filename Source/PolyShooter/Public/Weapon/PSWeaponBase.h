// PolyShooter By DChepurkin

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PSCoreTypes.h"
#include "PSWeaponBase.generated.h"

class APSMagazineBase;
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
	const FWeaponSoundData& GetSoundData() const { return WeaponSoundData; }
	const FWeaponUIData& GetWeaponUIData() const { return WeaponUIData; }
	UStaticMeshComponent* GetWeaponMesh() { return WeaponMesh; }

	virtual void StartFire();
	virtual void StopFire();
	virtual bool IsFire() { return FireInProgress; }	

	bool IsAmmoEmpty();
	bool IsClipEmpty();
	bool CanReload();

	virtual void SetVisibility(bool Visible);
	void ChangeClip();

	virtual void StartSetupMagazine();
	virtual void EndSetupMagazine();
	virtual void StartReload();
	virtual void OnEndFireAnim();

	void AddClips(int32 ClipsAmount);

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=PSWeaponBase)
	UStaticMeshComponent* WeaponMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=PSWeaponBase)
	UStaticMeshComponent* MagazineMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=PSWeaponBase, meta=(ClampMin = "0.0"))
	float Damage = 10.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=PSWeaponBase, meta=(ClampMin = "0.0"))
	float FireDistance = 1500.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=PSWeaponBase, meta=(ClampMin = "0.0"))
	float BulletSpread = 1.5f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=PSWeaponBase)
	FAmmoData DefaultAmmoData;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=PSWeaponBase)
	FWeaponData WeaponData;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=PSWeaponBase)
	FWeaponAnimData WeaponAnimData;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=PSWeaponBase)
	FWeaponSoundData WeaponSoundData;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=PSWeaponBase)
	FWeaponUIData WeaponUIData;

	UPROPERTY()
	APSMagazineBase* Magazine;

	bool FireInProgress = false;

	bool CanFire();
	bool GetTraceData(FVector& StartTrace, FVector& EndTrace);
	void MakeTrace(FHitResult& HitResult, const FVector& StartTrace, const FVector& EndTrace);

	virtual void MakeShot();	

	void SetMagazineVisible(bool Visibility);
	void SpawnMagazine(const FName& SocketName);
	UStaticMesh* GetMagazineMesh();

private:	
	FAmmoData AmmoData;

	bool GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation);
	void GetMuzzleSocketTransform(FVector& ViewLocation, FRotator& ViewRotation);
	void DecreaseAmmo();
	void SetInfinite(bool Infinite);
};
