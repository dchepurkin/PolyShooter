// PolyShooter By DChepurkin

#include "Character/PSMenuPlayerController.h"

void APSMenuPlayerController::BeginPlay()
{
	Super::BeginPlay();

	SetInputMode(FInputModeUIOnly());
	SetShowMouseCursor(true);
}
