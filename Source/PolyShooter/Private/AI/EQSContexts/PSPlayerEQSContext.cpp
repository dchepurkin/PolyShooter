// PolyShooter By DChepurkin

#include "AI/EQSContexts/PSPlayerEQSContext.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_Actor.h"

void UPSPlayerEQSContext::ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const
{
	const auto QueryOwner = Cast<AActor>(QueryInstance.Owner.Get());
	if(!QueryOwner) return;

	const auto BlackBoard = UAIBlueprintHelperLibrary::GetBlackboard(QueryOwner);
	if(!BlackBoard) return;

	const auto ContextActor = Cast<AActor>(BlackBoard->GetValueAsObject(EnemyActorKeyName));
	if(!ContextActor) return;

	UEnvQueryItemType_Actor::SetContextHelper(ContextData, ContextActor);
}
