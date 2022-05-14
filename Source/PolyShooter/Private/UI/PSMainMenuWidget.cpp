// PolyShooter By DChepurkin

#include "UI/PSMainMenuWidget.h"

#include "Components/Button.h"
#include "Kismet/KismetSystemLibrary.h"

void UPSMainMenuWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	QuitGameButton->OnPressed.AddDynamic(this, &UPSMainMenuWidget::OnQuitGame);
}

void UPSMainMenuWidget::OnQuitGame()
{
	if(GetWorld() && GetOwningPlayer())
		UKismetSystemLibrary::QuitGame(GetWorld(), GetOwningPlayer(), EQuitPreference::Quit, true);
}
