// PolyShooter By DChepurkin

#include "AI/Services/PSBTMakeNoiseService.h"

#include "AIController.h"
#include "PSAISense_Hearing.h"
#include "BehaviorTree/BlackboardComponent.h"

UPSBTMakeNoiseService::UPSBTMakeNoiseService()
{
	NodeName = "Make Noise";
	Interval = 0.5f;
	RandomDeviation = 0.0f;
}

void UPSBTMakeNoiseService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	UPSAISense_Hearing::ReportHearingEvent(GetWorld(), GetHearingActor(OwnerComp), GetNoiseMaker(OwnerComp));
}

AActor* UPSBTMakeNoiseService::GetHearingActor(UBehaviorTreeComponent& OwnerComp)
{
	const auto Controller = OwnerComp.GetAIOwner();
	if(!Controller) return nullptr;

	return Controller->GetPawn();
}

AActor* UPSBTMakeNoiseService::GetNoiseMaker(UBehaviorTreeComponent& OwnerComp)
{
	const auto Blackboard = OwnerComp.GetBlackboardComponent();
	if(!Blackboard) return nullptr;

	return Cast<AActor>(Blackboard->GetValueAsObject(EnemyActorKey.SelectedKeyName));
}
