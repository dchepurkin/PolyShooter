// PolyShooter By DChepurkin

#pragma once

#include "CoreMinimal.h"
#include "Character/PSCharacterBase.h"
#include "PSPlayerCharacter.generated.h"

class UCameraComponent;
class UPSWeaponComponent;

UCLASS()
class POLYSHOOTER_API APSPlayerCharacter : public APSCharacterBase
{
	GENERATED_BODY()

public:
	APSPlayerCharacter(const FObjectInitializer& ObjectInitializer);

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual USkeletalMeshComponent* GetMainMesh() const override { return FirstPersonMeshComponent; }

	virtual bool IsRunning() const override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category=Components)
	UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category=Components)
	USkeletalMeshComponent* FirstPersonMeshComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=Components)
	UStaticMeshComponent* MagazineMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category=Components)
	UPSWeaponComponent* WeaponComponent;

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
};
