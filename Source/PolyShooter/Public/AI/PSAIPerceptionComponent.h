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

private:
	AActor* GetPerceivedActor(const TSubclassOf<UAISense> Sence);
};
