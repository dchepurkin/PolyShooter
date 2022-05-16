// PolyShooter By DChepurkin

#include "UI/PSStartGameButtonWidget.h"

#include "PSGameModeBase.h"
#include "Components/Button.h"

void UPSStartGameButtonWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	StartGameButton->OnPressed.AddDynamic(this, &UPSStartGameButtonWidget::OnStartGame);
}

void UPSStartGameButtonWidget::OnStartGame()
{
	if(!GetWorld()) return;

	const auto GameMode = GetWorld()->GetAuthGameMode<APSGameModeBase>();
	if(!GameMode) return;

	GameMode->StartFirstLevel();
}
