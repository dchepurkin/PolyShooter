// PolyShooter By DChepurkin

#include "AI/Services/PSBTFireService.h"

#include "AIController.h"
#include "PSAnimInstance.h"
#include "PSWeaponComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogFireService, All, All);

UPSBTFireService::UPSBTFireService()
{
	NodeName = "Fire";
	Interval = 1.5f;
	RandomDeviation = 0.5f;
}

void UPSBTFireService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	const auto Blackboard = OwnerComp.GetBlackboardComponent();
	const auto HasAim = Blackboard && IsDistanceReadyToFire(Blackboard);

	if(GetWeaponComponent(OwnerComp))
	{
		HasAim
			? GetWeaponComponent(OwnerComp)->StartFire()
			: GetWeaponComponent(OwnerComp)->StopFire();
	}

	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}

void UPSBTFireService::OnSearchStart(FBehaviorTreeSearchData& SearchData)
{
	Super::OnSearchStart(SearchData);

	if(!GetWorld()) return;

	GetWorld()->GetTimerManager().SetTimer(FireTimerHandle, [&SearchData, this]() { StopFire(SearchData.OwnerComp); }, FireRate, true);
}

void UPSBTFireService::StopFire(const UBehaviorTreeComponent& OwnerComp)
{
	if(GetWeaponComponent(OwnerComp)) GetWeaponComponent(OwnerComp)->StopFire();
}

UPSWeaponComponent* UPSBTFireService::GetWeaponComponent(const UBehaviorTreeComponent& OwnerComp)
{
	const auto Controller = OwnerComp.GetAIOwner();
	if(!Controller || !Controller->GetPawn()) return nullptr;

	return Controller->GetPawn()->FindComponentByClass<UPSWeaponComponent>();
}

bool UPSBTFireService::IsDistanceReadyToFire(UBlackboardComponent* Blackboard)
{
	const auto EnemyActor = Cast<AActor>(Blackboard->GetValueAsObject(EnemyActorKey.SelectedKeyName));
	const auto Controller = Blackboard->GetOwner<AAIController>();
	if(!EnemyActor || !Controller) return false;

	const auto Pawn = Controller->GetPawn();

	return Pawn && Pawn->GetDistanceTo(EnemyActor) <= FireDistance;
}
