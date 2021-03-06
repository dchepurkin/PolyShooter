// PolyShooter By DChepurkin

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PSCharacterBase.generated.h"

class UPSWeaponComponent;
class UPSHealthComponent;

UCLASS()
class POLYSHOOTER_API APSCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	APSCharacterBase(const FObjectInitializer& ObjectInitializer);

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	virtual USkeletalMeshComponent* GetMainMesh() const { return GetMesh(); }
	virtual bool IsRunning() const { return false; }	

protected:
	virtual void BeginPlay() override;	

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=Components)
	UPSHealthComponent* HealthComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category=Components)
	UPSWeaponComponent* WeaponComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=PSCharacter)
	float DeathLifeSpan = 5.0f;

	virtual void OnDeath();
};
