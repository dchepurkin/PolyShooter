// PolyShooter By DChepurkin

#include "AI/Services/PSBTFireService.h"

#include "AIController.h"
#include "PSWeaponComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

UPSBTFireService::UPSBTFireService()
{
	NodeName = "Fire";
}

void UPSBTFireService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	const auto Blackboard = OwnerComp.GetBlackboardComponent();
	const auto Controller = OwnerComp.GetAIOwner();

	const auto HasAim = Blackboard && Blackboard->GetValueAsObject(EnemyActorKey.SelectedKeyName);

	if(Controller && Controller->GetPawn())
	{
		if(const auto WeaponComponent = Controller->GetPawn()->FindComponentByClass<UPSWeaponComponent>())
		{
			HasAim ? WeaponComponent->StartFire() : WeaponComponent->StopFire();
		}
	}

	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
