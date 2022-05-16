// PolyShooter By DChepurkin

#include "UI/PSPauseWidget.h"

#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"

DEFINE_LOG_CATEGORY_STATIC(LogPauseWidget, All, All);

void UPSPauseWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	ResumeGameButton->OnPressed.AddDynamic(this, &UPSPauseWidget::OnResumeGame);
}

void UPSPauseWidget::OnResumeGame()
{
	if(GetOwningPlayer()) GetOwningPlayer()->SetPause(false);
}
