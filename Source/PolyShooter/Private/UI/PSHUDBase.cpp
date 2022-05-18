// PolyShooter By DChepurkin

#include "UI/PSHUDBase.h"

#include "EngineUtils.h"
#include "PSWidgetBase.h"
#include "GameFramework/GameModeBase.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY_STATIC(LogHUDBase, All, All);

APSHUDBase::APSHUDBase()
{
	PrimaryActorTick.bTickEvenWhenPaused = true;
}

void APSHUDBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	LoadingScreenTimerManager.Tick(DeltaSeconds);
}

void APSHUDBase::CreateSubWidget(TSubclassOf<UPSWidgetBase> WidgetClass)
{
	if(!WidgetClass) return;

	if(const auto SubWidget = CreateWidget<UPSWidgetBase>(GetOwningPlayerController(), WidgetClass))
	{
		SubWidget->AddToViewport();
		SubWidget->Show();
	}
}

void APSHUDBase::ShowLoadingScreen()
{
	const auto Controller = GetOwningPlayerController();
	if(!Controller) return;

	Controller->SetShowMouseCursor(false);
	Controller->SetInputMode(FInputModeGameOnly());

	CreateSubWidget(LoadingScreenWidgetClass);
	LoadingScreenTimerManager.SetTimer(LoadingScreenTimer, this, &APSHUDBase::OnLoadingScreenTimer, LoadingScreenDelay, false);
}

void APSHUDBase::OnLoadingScreenTimer()
{
	LoadingScreenTimerManager.ClearTimer(LoadingScreenTimer);
	OnLoadingScreenFinished.Broadcast();
}
