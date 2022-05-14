// PolyShooter By DChepurkin

#include "UI/PSHUDBase.h"

#include "PSLevelGameModeBase.h"
#include "PSWidgetBase.h"

void APSHUDBase::BeginPlay()
{
	Super::BeginPlay();

	if(PlayerHUDWidgetClass)
		Widgets.Add(EGameState::InProgress, CreateWidget<UPSWidgetBase>(GetOwningPlayerController(), PlayerHUDWidgetClass, "PlayerHUDWidget"));

	if(PauseWidgetClass)
		Widgets.Add(EGameState::Pause, CreateWidget<UPSWidgetBase>(GetOwningPlayerController(), PauseWidgetClass, "PauseWidget"));

	if(GameOverWidgetClass)
		Widgets.Add(EGameState::GameOver, CreateWidget<UPSWidgetBase>(GetOwningPlayerController(), GameOverWidgetClass, "GameOverWidget"));

	for(const auto WidgetPair : Widgets)
	{
		const auto Widget = WidgetPair.Value;
		if(!Widget) continue;

		Widget->AddToViewport();
		Widget->SetVisibility(ESlateVisibility::Hidden);
	}

	if(GetWorld())
	{
		const auto GameMode = GetWorld()->GetAuthGameMode<APSLevelGameModeBase>();
		if(GameMode) GameMode->OnGameStateChanged.AddUObject(this, &APSHUDBase::OnGameStateChanged);
	}
}

void APSHUDBase::OnGameStateChanged(EGameState GameState)
{
	if(CurrentWidget) CurrentWidget->SetVisibility(ESlateVisibility::Hidden);

	if(Widgets.Contains(GameState)) CurrentWidget = Widgets[GameState];

	if(CurrentWidget)
	{
		CurrentWidget->SetVisibility(ESlateVisibility::Visible);
		CurrentWidget->Show();
	}
}
