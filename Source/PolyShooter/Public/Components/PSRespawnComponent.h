// PolyShooter By DChepurkin

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PSRespawnComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class POLYSHOOTER_API UPSRespawnComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPSRespawnComponent();

	void StartRespawn();

	int32 GetRespawnCountDown() const { return RespawnCountDown; }

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=PSRespawnComponent, meta=(ClampMin = "0"))
	int32 RespawnTime = 5;

private:
	FTimerHandle RespawnTimerHandle;
	int32 RespawnCountDown = RespawnTime;

	bool CanRespawn() const;
	void GameOver();
	void UpdateRespawnTimer();
};
