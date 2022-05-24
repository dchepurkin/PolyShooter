// PolyShooter By DChepurkin

#include "AI/PSAIPerceptionComponent.h"

#include "PSHealthComponent.h"
#include "PSPlayerCharacter.h"
#include "Perception/AISense_Damage.h"
#include "Perception/AISense_Sight.h"

DEFINE_LOG_CATEGORY_STATIC(LogPSAIPerception, All, All);

AActor* UPSAIPerceptionComponent::GetEnemy()
{
	const auto EnemyActor = GetPerceivedActor(UAISense_Sight::StaticClass());
	return EnemyActor ? EnemyActor : GetPerceivedActor(UAISense_Damage::StaticClass());
}

void UPSAIPerceptionComponent::OnRegister()
{
	Super::OnRegister();

	OnTargetPerceptionInfoUpdated.AddDynamic(this, &UPSAIPerceptionComponent::OnPerseption);
}

void UPSAIPerceptionComponent::OnPerseption(const FActorPerceptionUpdateInfo& UpdateInfo)
{
	UE_LOG(LogPSAIPerception, Display, TEXT("TEST"));
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
