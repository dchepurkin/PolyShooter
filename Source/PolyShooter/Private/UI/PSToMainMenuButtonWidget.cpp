// PolyShooter By DChepurkin

#include "UI/PSToMainMenuButtonWidget.h"

#include "PSHUDLevel.h"
#include "Components/Button.h"

void UPSToMainMenuButtonWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	
	ToMainMenuButton->OnPressed.AddDynamic(this, &UPSToMainMenuButtonWidget::OnToMainMenu);
}

void UPSToMainMenuButtonWidget::OnToMainMenu()
{
	if(!GetOwningPlayer() || !GetOwningPlayer()->GetHUD<APSHUDLevel>()) return;
	GetOwningPlayer()->GetHUD<APSHUDLevel>()->ShowQuitGameQuiestion(true);
}
