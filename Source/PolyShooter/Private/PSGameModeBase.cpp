// PolyShooter By DChepurkin

#include "PSGameModeBase.h"

#include "PSPlayerCharacter.h"
#include "PSPlayerController.h"

APSGameModeBase::APSGameModeBase()
{
	DefaultPawnClass = APSPlayerCharacter::StaticClass();
	PlayerControllerClass = APSPlayerController::StaticClass();
}
