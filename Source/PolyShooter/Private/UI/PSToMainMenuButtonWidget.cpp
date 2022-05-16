// PolyShooter By DChepurkin

#include "UI/PSToMainMenuButtonWidget.h"

#include "PSHUDBase.h"
#include "PSQuitGameQuestionWidget.h"
#include "Components/Button.h"

void UPSToMainMenuButtonWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	
	ToMainMenuButton->OnPressed.AddDynamic(this, &UPSToMainMenuButtonWidget::OnToMainMenu);
}

void UPSToMainMenuButtonWidget::OnToMainMenu()
{
	if(!GetOwningPlayer() || !GetOwningPlayer()->GetHUD<APSHUDBase>()) return;
	GetOwningPlayer()->GetHUD<APSHUDBase>()->ShowQuitGameQuiestion(true);
}
