// PolyShooter By DChepurkin

#include "UI/PSHUDMenu.h"
#include "PSWidgetBase.h"

DEFINE_LOG_CATEGORY_STATIC(LogHUDMenu, All, All);

void APSHUDMenu::BeginPlay()
{
	Super::BeginPlay();

	if(MainMenuWidgetClass)
	{
		if(const auto MainMenuWidget = CreateWidget<UPSWidgetBase>(GetOwningPlayerController(), MainMenuWidgetClass))
		{
			MainMenuWidget->AddToViewport();
			MainMenuWidget->Show();
		}
	}
}
