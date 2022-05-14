// PolyShooter By DChepurkin

#include "UI/PSPauseWidget.h"

#include "Components/Button.h"

void UPSPauseWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	ResumeGameButton->OnPressed.AddDynamic(this, &UPSPauseWidget::OnResumeGame);
}

void UPSPauseWidget::OnResumeGame()
{
	if(GetOwningPlayer()) GetOwningPlayer()->SetPause(false);
}
