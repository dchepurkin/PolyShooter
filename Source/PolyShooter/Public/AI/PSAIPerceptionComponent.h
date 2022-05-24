// PolyShooter By DChepurkin

#pragma once

#include "CoreMinimal.h"
#include "Perception/AIPerceptionComponent.h"
#include "PSAIPerceptionComponent.generated.h"

UCLASS()
class POLYSHOOTER_API UPSAIPerceptionComponent : public UAIPerceptionComponent
{
	GENERATED_BODY()

public:
	AActor* GetEnemy();
	virtual void OnRegister() override;

private:
	AActor* GetPerceivedActor(const TSubclassOf<UAISense> Sence);

	UFUNCTION()
	void OnPerseption(const FActorPerceptionUpdateInfo& UpdateInfo);
};
