// PolyShooter By DChepurkin

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "PSBTFireService.generated.h"

UCLASS()
class POLYSHOOTER_API UPSBTFireService : public UBTService
{
	GENERATED_BODY()

public:
	UPSBTFireService();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category=PSFireService)
	FBlackboardKeySelector EnemyActorKey;
	
};
