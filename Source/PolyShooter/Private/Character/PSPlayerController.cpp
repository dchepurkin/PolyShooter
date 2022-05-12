// PolyShooter By DChepurkin

#include "Character/PSPlayerController.h"

#include "PSGameInstance.h"
#include "PSHealthComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogPSPlayerController, All, All);

APSPlayerController::APSPlayerController()
{
	RespawnComponent = CreateDefaultSubobject<UPSRespawnComponent>("RespawnComponent");
}

void APSPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if(const auto HealthComponent = InPawn->FindComponentByClass<UPSHealthComponent>())
	{
		HealthComponent->OnDeath.AddUObject(this, &APSPlayerController::OnDeath);
	}
}

void APSPlayerController::OnDeath()
{
	ChangeState(NAME_Spectating);
	if(RespawnComponent) RespawnComponent->StartRespawn();
	if(GetGameInstance<UPSGameInstance>()) GetGameInstance<UPSGameInstance>()->OnDeath();
}
