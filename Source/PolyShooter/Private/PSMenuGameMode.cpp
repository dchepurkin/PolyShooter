// PolyShooter By DChepurkin

#include "PSMenuGameMode.h"

#include "PSHUDMenu.h"
#include "PSMenuPlayerController.h"

APSMenuGameMode::APSMenuGameMode()
{
	PlayerControllerClass = APSMenuPlayerController::StaticClass();
	HUDClass = APSHUDMenu::StaticClass();
}
