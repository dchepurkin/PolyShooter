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
	if(const auto Blackboard = OwnerComp.GetBlackboardComponent())
	{
		const auto AIController = OwnerComp.GetAIOwner();
		const auto AIPerceptionComponent = AIController->FindComponentByClass<UPSAIPerceptionComponent>();

		Blackboard->SetValueAsObject(EnemyActorKey.SelectedKeyName, AIPerceptionComponent->GetEnemy());
	}

	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
