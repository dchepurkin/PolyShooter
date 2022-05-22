// PolyShooter By DChepurkin

#include "Character/AI/PSAIController.h"

#include "AI/PSAIPerceptionComponent.h"

APSAIController::APSAIController()
{
	PrimaryActorTick.bCanEverTick = true;
	
	AIPerceptionComponent = CreateDefaultSubobject<UPSAIPerceptionComponent>("AIPerceptionComponent");
	SetPerceptionComponent(*AIPerceptionComponent);
}

void APSAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	SetFocus(GetEnemyToFocus());
}

AActor* APSAIController::GetEnemyToFocus()
{
	return AIPerceptionComponent->GetEnemy();
}

void APSAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	RunBehaviorTree(BehaviorTreeAsset);
}


