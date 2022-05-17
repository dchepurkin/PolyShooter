// PolyShooter By DChepurkin

#include "UI/PSHUDLevel.h"

#include "PSLevelGameModeBase.h"

void APSHUDLevel::BeginPlay()
{
	Super::BeginPlay();

	for(const auto& WidgetData : StateWidgetsData)
	{
		if(WidgetData.WidgetClass)
			Widgets.Add(WidgetData.GameState, CreateWidget<UPSWidgetBase>(GetOwningPlayerController(), WidgetData.WidgetClass));
	}

	for(const auto& WidgetPair : Widgets)
	{
		const auto Widget = WidgetPair.Value;
		if(!Widget) continue;

		Widget->AddToViewport();
		Widget->SetVisibility(ESlateVisibility::Hidden);
	}

	if(GetWorld())
	{
		const auto GameMode = GetWorld()->GetAuthGameMode<APSLevelGameModeBase>();
		if(GameMode) GameMode->OnGameStateChanged.AddUObject(this, &APSHUDLevel::OnGameStateChanged);
	}
}

void APSHUDLevel::OnGameStateChanged(EGameState GameState)
{
	if(CurrentWidget) CurrentWidget->SetVisibility(ESlateVisibility::Hidden);

	if(Widgets.Contains(GameState)) CurrentWidget = Widgets[GameState];

	if(CurrentWidget)
	{
		CurrentWidget->SetVisibility(ESlateVisibility::Visible);
		CurrentWidget->Show();
	}
}

void APSHUDLevel::ShowQuitGameQuiestion(bool Show)
{
	if(CurrentWidget) CurrentWidget->SetVisibility(Show ? ESlateVisibility::Hidden : ESlateVisibility::Visible);
	if(Show) CreateSubWidget(QuitGameQuestionWidgetClass);
}
