// PolyShooter By DChepurkin

#include "PSGameModeBase.h"

#include "PSPlayerCharacter.h"
#include "PSPlayerController.h"
#include "UI/PSHUDBase.h"

APSGameModeBase::APSGameModeBase()
{
	DefaultPawnClass = APSPlayerCharacter::StaticClass();
	PlayerControllerClass = APSPlayerController::StaticClass();
	HUDClass = APSHUDBase::StaticClass();
}
