// PolyShooter By DChepurkin

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PSDamageActor.generated.h"

UCLASS()
class POLYSHOOTER_API APSDamageActor : public AActor
{
	GENERATED_BODY()

public:
	APSDamageActor();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category=PSDamageActor, meta=(ClampMin = "0.0"))
	float Damage = 1.0f;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category=PSDamageActor, meta=(ClampMin = "0.0"))
	float DamageRadius = 150.0f;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category=PSDamageActor, meta=(ClampMin = "0.0"))
	float DamageRate = 1.0f;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category=PSDamageActor)
	bool DoFullDamage = true;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category=PSDamageActor)
	FColor Color = FColor::Red;

private:
	FTimerHandle TimerHandle;

	void OnTimer();
};
