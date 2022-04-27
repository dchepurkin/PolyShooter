// PolyShooter By DChepurkin

#include "UI/PSHUDBase.h"
#include "Blueprint/UserWidget.h"

void APSHUDBase::BeginPlay()
{
	Super::BeginPlay();

	const auto PlayerHUDWidget = CreateWidget<UUserWidget>(GetOwningPlayerController(), PlayerHUDWidgetClass,"PlayerHUDWidget");
	if(PlayerHUDWidget) PlayerHUDWidget->AddToViewport();
	
}
