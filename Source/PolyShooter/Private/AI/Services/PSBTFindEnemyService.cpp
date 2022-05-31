// PolyShooter By DChepurkin

#include "AI/Services/PSBTFindEnemyService.h"

#include "AIController.h"
#include "AI/PSAIPerceptionComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

UPSBTFindEnemyService::UPSBTFindEnemyService()
{
	NodeName = "Find Enemy";
}

void UPSBTFindEnemyService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	const auto Blackboard = OwnerComp.GetBlackboardComponent();
	if(!Blackboard) return;

	const auto AIController = OwnerComp.GetAIOwner();
	if(!AIController) return;

	const auto AIPerceptionComponent = AIController->FindComponentByClass<UPSAIPerceptionComponent>();
	if(!AIPerceptionComponent) return;

	Blackboard->SetValueAsObject(EnemyActorKey.SelectedKeyName, AIPerceptionComponent->GetEnemy());
}
