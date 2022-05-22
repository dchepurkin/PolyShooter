// PolyShooter By DChepurkin

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "EnvironmentQuery/EnvQueryContext.h"
#include "PSPlayerEQSContext.generated.h"

UCLASS()
class POLYSHOOTER_API UPSPlayerEQSContext : public UEnvQueryContext
{
	GENERATED_BODY()

public:
	virtual void ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const override;

protected:
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category=PSEQS)
	FName EnemyActorKeyName = "EnemyActor";
};
