// PolyShooter By DChepurkin

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PSCoreTypes.h"
#include "PSWeaponFXComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class POLYSHOOTER_API UPSWeaponFXComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPSWeaponFXComponent();

	void PlayImpactFX(const FHitResult& HitResult);

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=PSWeaponFX)
	FImpactData DefaultImpactData;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=PSWeaponFX)
	TMap<UPhysicalMaterial*, FImpactData> ImpactData;

private:
	void SpawnDecal(const FHitResult& HitResult, FImpactData& CurrentImpactData);
};
