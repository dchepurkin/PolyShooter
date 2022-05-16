// PolyShooter By DChepurkin

#include "UI/PSHUDBase.h"

#include "PSLevelGameModeBase.h"
#include "PSWidgetBase.h"

DEFINE_LOG_CATEGORY_STATIC(LogHUDBase, All, All);

void APSHUDBase::ShowQuitGameQuiestion(bool Show)
{
	if(CurrentWidget) CurrentWidget->SetVisibility(Show ? ESlateVisibility::Hidden : ESlateVisibility::Visible);
	if(Show) CreateSubWidget(QuitGameQuestionWidgetClass);
}

void APSHUDBase::BeginPlay()
{
	Super::BeginPlay();

	for(const auto& StateWidgetClass : StateWidgetsClasses)
	{
		if(StateWidgetClass.Value)
			Widgets.Add(StateWidgetClass.Key, CreateWidget<UPSWidgetBase>(GetOwningPlayerController(), StateWidgetClass.Value));
	}

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

void APSHUDBase::CreateSubWidget(TSubclassOf<UPSWidgetBase> WidgetClass)
{
	if(!WidgetClass) return;
	
	if(const auto SubWidget = CreateWidget<UPSWidgetBase>(GetOwningPlayerController(), WidgetClass))
	{
		SubWidget->AddToViewport();
		SubWidget->Show();
	}
}
