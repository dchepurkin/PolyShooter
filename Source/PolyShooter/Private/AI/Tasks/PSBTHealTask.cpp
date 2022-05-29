// PolyShooter By DChepurkin

#include "AI/Tasks/PSBTHealTask.h"

#include "AIController.h"
#include "PSHealthComponent.h"

UPSBTHealTask::UPSBTHealTask()
{
	NodeName = "Recovery Health";
}

EBTNodeResult::Type UPSBTHealTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const auto Controller = OwnerComp.GetAIOwner();
	if(!Controller) return EBTNodeResult::Failed;

	const auto Pawn = Controller->GetPawn();
	if(!Pawn) return EBTNodeResult::Failed;

	const auto HealthComponent = Pawn->FindComponentByClass<UPSHealthComponent>();
	if(!HealthComponent || HealthComponent->IsDead()) return EBTNodeResult::Failed;

	if(HealthComponent->GetHealthPercent() < 1.f) HealthComponent->MakeHeal();

	return EBTNodeResult::Succeeded;
}
