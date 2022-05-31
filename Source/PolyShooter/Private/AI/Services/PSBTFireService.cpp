// PolyShooter By DChepurkin

#include "AI/Services/PSBTFireService.h"

#include "AIController.h"
#include "PSWeaponComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/KismetMathLibrary.h"

DEFINE_LOG_CATEGORY_STATIC(LogFireService, All, All);

UPSBTFireService::UPSBTFireService()
{
	NodeName = "Fire";
	Interval = 1.5f;
	RandomDeviation = 0.5f;
	bCreateNodeInstance = true;
}

void UPSBTFireService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	const auto Blackboard = OwnerComp.GetBlackboardComponent();
	const auto HasAim = Blackboard && IsDistanceReadyToFire(Blackboard) && IsPlayerVisible(&OwnerComp);

	if(GetWeaponComponent(&OwnerComp))
	{
		HasAim
			? GetWeaponComponent(&OwnerComp)->StartFire()
			: GetWeaponComponent(&OwnerComp)->StopFire();
	}

	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}

void UPSBTFireService::OnSearchStart(FBehaviorTreeSearchData& SearchData)
{
	Super::OnSearchStart(SearchData);

	if(GetWorld() && !GetWorld()->GetTimerManager().IsTimerActive(StopFireTimerHandle))
	{
		const FTimerDelegate StopFireDelegate = FTimerDelegate::CreateUObject(this, &UPSBTFireService::StopFire, &SearchData.OwnerComp);
		GetWorld()->GetTimerManager().SetTimer(StopFireTimerHandle, StopFireDelegate, FireTime, true);
	}
}

void UPSBTFireService::StopFire(UBehaviorTreeComponent* OwnerComp)
{
	if(GetWeaponComponent(OwnerComp)) GetWeaponComponent(OwnerComp)->StopFire();
	else GetWorld()->GetTimerManager().ClearAllTimersForObject(this);
}

UPSWeaponComponent* UPSBTFireService::GetWeaponComponent(UBehaviorTreeComponent* OwnerComp)
{
	const auto Controller = OwnerComp->GetAIOwner();
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

bool UPSBTFireService::IsPlayerVisible(UBehaviorTreeComponent* OwnerComp)
{
	if(!GetWorld() || !OwnerComp) return false;

	const auto Controller = OwnerComp->GetAIOwner();
	if(!Controller) return false;

	const auto ControlledPawn = Controller->GetPawn();
	if(!ControlledPawn) return false;

	const auto Blackboard = OwnerComp->GetBlackboardComponent();
	if(!Blackboard) return false;

	const auto EnemyActor = Cast<AActor>(Blackboard->GetValueAsObject(EnemyActorKey.SelectedKeyName));
	if(!EnemyActor) return false;

	FHitResult HitResult;
	FCollisionQueryParams CollisionQueryParams;
	CollisionQueryParams.AddIgnoredActor(ControlledPawn);

	GetWorld()->LineTraceSingleByChannel(HitResult, ControlledPawn->GetActorLocation(), EnemyActor->GetActorLocation(), ECC_GameTraceChannel1,
	                                     CollisionQueryParams);

	return !HitResult.bBlockingHit;
}
