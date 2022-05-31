// PolyShooter By DChepurkin

#include "Character/AI/PSAIController.h"

#include "AI/PSAIPerceptionComponent.h"
#include "Perception/AISense_Damage.h"
#include "Sense/PSAISense_Hearing.h"

DEFINE_LOG_CATEGORY_STATIC(LogPSAIController, All, All);

APSAIController::APSAIController()
{
	PrimaryActorTick.bCanEverTick = true;

	AIPerceptionComponent = CreateDefaultSubobject<UPSAIPerceptionComponent>("AIPerceptionComponent");
	SetPerceptionComponent(*AIPerceptionComponent);
}

void APSAIController::OnTakeDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy,
                                   AActor* DamageCauser)
{
	ReportDamageEvent(Damage, InstigatedBy);
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

void APSAIController::ReportDamageEvent(float Damage, AController* InstigatedBy)
{
	if(!GetWorld() ||
		!GetPawn() ||
		!InstigatedBy ||
		!InstigatedBy->GetPawn())
		return;

	UAISense_Damage::ReportDamageEvent(GetWorld(),
	                                   GetPawn(),
	                                   InstigatedBy->GetPawn(), Damage,
	                                   InstigatedBy->GetPawn()->GetActorLocation(),
	                                   GetPawn()->GetActorLocation());
}

void APSAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if(InPawn)
	{
		RunBehaviorTree(BehaviorTreeAsset);
		InPawn->OnTakeAnyDamage.AddDynamic(this, &APSAIController::OnTakeDamage);
	}
}
