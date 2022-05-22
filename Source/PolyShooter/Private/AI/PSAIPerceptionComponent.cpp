// PolyShooter By DChepurkin

#include "AI/PSAIPerceptionComponent.h"

#include "PSHealthComponent.h"
#include "PSPlayerCharacter.h"
#include "Perception/AISense_Sight.h"

DEFINE_LOG_CATEGORY_STATIC(LogPSAIPerception, All, All);

AActor* UPSAIPerceptionComponent::GetEnemy() const
{
	TArray<AActor*> PerceivedActors;

	GetKnownPerceivedActors(UAISense_Sight::StaticClass(), PerceivedActors);
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
