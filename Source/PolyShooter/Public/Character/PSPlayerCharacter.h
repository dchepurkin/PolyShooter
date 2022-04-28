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

	bool IsRunning() const;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category=Components)
	UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category=Components)
	USkeletalMeshComponent* FirstPersonMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category=Components)
	UPSWeaponComponent* WeaponComponent;

	virtual void BeginPlay() override;

private:
	bool WantsToRun = false;
	bool IsMovingForward = false;

	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);

	void OnStartRun();
	void OnStopRun();
};
