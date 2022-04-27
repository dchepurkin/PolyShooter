// PolyShooter By DChepurkin

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PSHealthComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnDeathSignature)

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class POLYSHOOTER_API UPSHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPSHealthComponent();

	FOnDeathSignature OnDeath;

	UFUNCTION(BlueprintCallable)
	float GetHealthPercent() const { return Health / MaxHealth; }

	bool IsDead() const { return FMath::IsNearlyZero(Health); }

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=Health)
	float MaxHealth = 100.0f;

private:	
	float Health = 0.0f;

	UFUNCTION()
	void OnTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
	                     AController* InstigatedBy, AActor* DamageCauser);

	void SetHealth(float NewHealth);

	void ApplyDamage(float Damage);
};
