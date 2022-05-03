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

	void SetDirection(const FVector& Direction);

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

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=PSProjectile)
	bool IgnoreDamageSelf = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=PSProjectile, meta=(ClampMin = "1.0"))
	float LifeTime = 5.0f;

private:
	FVector ShotDirection = FVector::ZeroVector;
	
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	                    FVector NormalImpulse, const FHitResult& Hit);

	void MakeDamage();
	AController* GetController() const;	
};
