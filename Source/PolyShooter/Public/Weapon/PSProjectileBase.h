// PolyShooter By DChepurkin

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PSProjectileBase.generated.h"

class UProjectileMovementComponent;
class USphereComponent;

UCLASS()
class POLYSHOOTER_API APSProjectileBase : public AActor
{
	GENERATED_BODY()

public:
	APSProjectileBase();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=Components)
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=Components)
	UProjectileMovementComponent* ProjectileMovement;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=Components)
	USphereComponent* ProjectileCollision;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=PSProjectile, meta=(ClampMin = "0.0"))
	float Damage = 20.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=PSProjectile, meta=(ClampMin = "0.0"))
	float DamageRadius = 400.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=PSProjectile)
	bool DoFullDamage = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=PSProjectile, meta=(ClampMin = "1.0"))
	float LifeTime = 5.0f;

private:
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	                    int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void MakeDamage(AActor* DamagedActor);
};
