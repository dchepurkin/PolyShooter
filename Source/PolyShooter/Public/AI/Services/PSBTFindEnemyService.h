// PolyShooter By DChepurkin

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "PSBTFindEnemyService.generated.h"

UCLASS()
class POLYSHOOTER_API UPSBTFindEnemyService : public UBTService
{
	GENERATED_BODY()

public:
	UPSBTFindEnemyService();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category=PSFindEnemy)
	FBlackboardKeySelector EnemyActorKey;
	
};
