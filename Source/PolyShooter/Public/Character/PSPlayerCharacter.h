// PolyShooter By DChepurkin

#pragma once

#include "CoreMinimal.h"
#include "PSCoreTypes.h"
#include "Character/PSCharacterBase.h"
#include "PSPlayerCharacter.generated.h"

class APSWeaponBase;
class UCameraComponent;

UCLASS()
class POLYSHOOTER_API APSPlayerCharacter : public APSCharacterBase
{
	GENERATED_BODY()

public:
	APSPlayerCharacter(const FObjectInitializer& ObjectInitializer);

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual USkeletalMeshComponent* GetMainMesh() const override { return FirstPersonMeshComponent; }

	TMap<TSubclassOf<APSWeaponBase>, FAmmoData> GetWeaponInfo() const;
	void LoadWeaponInfo(TMap<TSubclassOf<APSWeaponBase>, FAmmoData>& WeaponsInfo);

	virtual bool IsRunning() const override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category=Components)
	UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category=Components)
	USkeletalMeshComponent* FirstPersonMeshComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=Components)
	UStaticMeshComponent* MagazineMesh;

	virtual void BeginPlay() override;
	virtual void OnDeath() override;

private:
	bool WantsToRun = false;
	bool IsMovingForward = false;

	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);

	void StartRun();
	void StopRun();

	void StartFire();
	void StopFire();

	bool CanFire();
};
