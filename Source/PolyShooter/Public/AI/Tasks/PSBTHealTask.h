// PolyShooter By DChepurkin

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "PSBTHealTask.generated.h"

UCLASS()
class POLYSHOOTER_API UPSBTHealTask : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UPSBTHealTask();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};
