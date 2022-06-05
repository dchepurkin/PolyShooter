// PolyShooter By DChepurkin

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "PSBTRouteTask.generated.h"

UCLASS()
class POLYSHOOTER_API UPSBTRouteTask : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UPSBTRouteTask();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category=PSTask)
	FBlackboardKeySelector TargetLocationKey;
};
