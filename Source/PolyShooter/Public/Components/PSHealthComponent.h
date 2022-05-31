// PolyShooter By DChepurkin

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PSHealthComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnDeathSignature);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHealthChangedSignature, float);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class POLYSHOOTER_API UPSHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPSHealthComponent();

	FOnDeathSignature OnDeath;
	FOnHealthChangedSignature OnHealthChanged;

	UFUNCTION(BlueprintCallable)
	float GetHealthPercent() const { return Health / MaxHealth; }

	bool IsDead() const { return FMath::IsNearlyZero(Health); }
	void MakeHeal(const float HealthAmount);
	void MakeHeal();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=Health)
	float MaxHealth = 100.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=Health)
	FVector2D LandedDamageVelocity = FVector2D(800.0, 1400.0);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=Health)
	FVector2D LandedDamage = FVector2D(0.0, MaxHealth);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=Health)
	TSubclassOf<UCameraShakeBase> DamageCameraShake;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Health|AutoHeal")
	bool AutoHealEnabled = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Health|AutoHeal",
		meta=(ClampMin = "0.001", EditCondition = AutoHealEnabled))
	float AutoHealDelay = 2.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Health|AutoHeal",
		meta=(ClampMin = "0.001", EditCondition = AutoHealEnabled))
	float AutoHealRate = 0.01f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Health|AutoHeal",
		meta=(ClampMin = "0.001", EditCondition = AutoHealEnabled))
	float AutoHealAmount = 0.05f;

private:
	float Health = 0.0f;
	FTimerHandle AutoHealTimerHandle;

	UFUNCTION()
	void OnTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
	                     AController* InstigatedBy, AActor* DamageCauser);

	UFUNCTION()
	void OnLanded(const FHitResult& Hit);

	void SetHealth(float NewHealth);
	void ApplyDamage(float Damage);
	void SetAutoHealTimer(const bool Enabled);
	void AutoHeal();
	void PlayDamageCameraShake() const;
};
