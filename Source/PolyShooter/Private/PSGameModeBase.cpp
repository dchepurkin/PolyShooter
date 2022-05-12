// PolyShooter By DChepurkin

#include "PSGameModeBase.h"

#include "PSPlayerCharacter.h"
#include "PSPlayerController.h"
#include "UI/PSHUDBase.h"

DEFINE_LOG_CATEGORY_STATIC(LogPSGameMode, All, All);

APSGameModeBase::APSGameModeBase()
{
	DefaultPawnClass = APSPlayerCharacter::StaticClass();
	PlayerControllerClass = APSPlayerController::StaticClass();
	HUDClass = APSHUDBase::StaticClass();
}

void APSGameModeBase::RespawnPlayer(AController* Controller)
{
	if(!Controller) return;
	RestartPlayer(Controller);
}
