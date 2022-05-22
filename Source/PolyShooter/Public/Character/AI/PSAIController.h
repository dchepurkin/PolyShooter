// PolyShooter By DChepurkin

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "PSAIController.generated.h"

class UPSAIPerceptionComponent;

UCLASS()
class POLYSHOOTER_API APSAIController : public AAIController
{
	GENERATED_BODY()

public:
	APSAIController();

protected:
	virtual void OnPossess(APawn* InPawn) override;
	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=PSAIController)
	UBehaviorTree* BehaviorTreeAsset;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=PSAIController)
	UPSAIPerceptionComponent* AIPerceptionComponent;

private:
	AActor* GetEnemyToFocus();
};
