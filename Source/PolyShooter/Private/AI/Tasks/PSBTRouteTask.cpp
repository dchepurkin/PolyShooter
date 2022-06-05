// PolyShooter By DChepurkin

#include "AI/Tasks/PSBTRouteTask.h"

#include "AIController.h"
#include "PSBOTMovementComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

UPSBTRouteTask::UPSBTRouteTask()
{
	NodeName = "Get Route Point";
}

EBTNodeResult::Type UPSBTRouteTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const auto Blackboard = OwnerComp.GetBlackboardComponent();
	const auto Controller = OwnerComp.GetAIOwner();
	if(!Controller || !Blackboard) return EBTNodeResult::Failed;

	const auto Pawn = Controller->GetPawn();
	if(!Pawn) return EBTNodeResult::Failed;

	const auto MovementComponent = Pawn->FindComponentByClass<UPSBOTMovementComponent>();
	if(!MovementComponent) return EBTNodeResult::Failed;

	Blackboard->SetValueAsVector(TargetLocationKey.SelectedKeyName, MovementComponent->GetNextPointLocation());

	return EBTNodeResult::Succeeded;
}
