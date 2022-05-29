// PolyShooter By DChepurkin

#include "AI/PSAIPerceptionComponent.h"

#include "PSHealthComponent.h"
#include "PSPlayerCharacter.h"
#include "Perception/AISense_Damage.h"
#include "Perception/AISense_Hearing.h"
#include "Perception/AISense_Sight.h"

DEFINE_LOG_CATEGORY_STATIC(LogPSAIPerception, All, All);

AActor* UPSAIPerceptionComponent::GetEnemy()
{
	auto EnemyActor = GetPerceivedActor(UAISense_Sight::StaticClass());
	if(!EnemyActor) EnemyActor = GetPerceivedActor(UAISense_Damage::StaticClass());

	return EnemyActor ? EnemyActor : GetPerceivedActor(UAISense_Hearing::StaticClass());
}

AActor* UPSAIPerceptionComponent::GetPerceivedActor(const TSubclassOf<UAISense> Sence)
{
	TArray<AActor*> PerceivedActors;

	GetKnownPerceivedActors(Sence, PerceivedActors);
	if(!PerceivedActors.Num()) return nullptr;

	for(const auto PerceivedActor : PerceivedActors)
	{
		if(PerceivedActor->IsA(APSPlayerCharacter::StaticClass()) &&
			PerceivedActor->FindComponentByClass<UPSHealthComponent>() &&
			!PerceivedActor->FindComponentByClass<UPSHealthComponent>()->IsDead())

			return PerceivedActor;
	}

	return nullptr;
}
