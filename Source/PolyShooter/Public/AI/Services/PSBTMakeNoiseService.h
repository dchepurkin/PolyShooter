// PolyShooter By DChepurkin

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "PSBTMakeNoiseService.generated.h"

UCLASS()
class POLYSHOOTER_API UPSBTMakeNoiseService : public UBTService
{
	GENERATED_BODY()

public:
	UPSBTMakeNoiseService();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category=MakeNoise)
	FBlackboardKeySelector EnemyActorKey;

private:
	AActor* GetHearingActor(UBehaviorTreeComponent& OwnerComp);
	AActor* GetNoiseMaker(UBehaviorTreeComponent& OwnerComp);
};
