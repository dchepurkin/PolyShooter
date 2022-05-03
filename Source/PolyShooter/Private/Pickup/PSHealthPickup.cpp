// PolyShooter By DChepurkin

#include "Pickup/PSHealthPickup.h"

#include "PSHealthComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogPSHealthPickup, All, All);

bool APSHealthPickup::CanTake(AActor* OtherActor)
{
	const auto HealthComponent = OtherActor->FindComponentByClass<UPSHealthComponent>();
	return Super::CanTake(OtherActor) && !FMath::IsNearlyEqual(HealthComponent->GetHealthPercent(), 1.0);
}

void APSHealthPickup::TakePickup(AActor* OtherActor)
{
	const auto HealthComponent = OtherActor->FindComponentByClass<UPSHealthComponent>();
	if(!HealthComponent) return;

	HealthComponent->MakeHeal(HealthAmount);

	Super::TakePickup(OtherActor);
}
