// PolyShooter By DChepurkin

#include "Character/PSPlayerController.h"
#include "PSHealthComponent.h"

void APSPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	if(!InPawn) return;

	const auto HealthComponent = InPawn->FindComponentByClass<UPSHealthComponent>();
	if(!HealthComponent) return;

	HealthComponent->OnDeath.AddUObject(this, &APSPlayerController::OnDeath);
}

void APSPlayerController::OnDeath()
{
	ChangeState(NAME_Spectating);
}
