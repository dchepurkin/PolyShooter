// PolyShooter By DChepurkin

#include "Character/PSPlayerController.h"

#include "PSGameInstance.h"
#include "PSLevelGameModeBase.h"
#include "PSHealthComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogPSPlayerController, All, All);

APSPlayerController::APSPlayerController()
{
	RespawnComponent = CreateDefaultSubobject<UPSRespawnComponent>("RespawnComponent");
}

bool APSPlayerController::SetPause(bool bPause, FCanUnpause CanUnpauseDelegate)
{
	if(!GetWorld()) return false;

	const auto GameMode = GetWorld()->GetAuthGameMode<APSLevelGameModeBase>();
	if(!GameMode || GameMode->GetGameState() == EGameState::GameOver) return false;

	GameMode->SetGameState(!IsPaused() ? EGameState::Pause : EGameState::InProgress);
	return Super::SetPause(bPause, CanUnpauseDelegate);
}

void APSPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if(const auto HealthComponent = InPawn->FindComponentByClass<UPSHealthComponent>())
	{
		HealthComponent->OnDeath.AddUObject(this, &APSPlayerController::OnDeath);
	}
}

void APSPlayerController::BeginPlay()
{
	Super::BeginPlay();

	InputComponent->BindAction("Pause", IE_Pressed, this, &APSPlayerController::OnPauseGame);

	const auto GameMode = GetWorld()->GetAuthGameMode<APSLevelGameModeBase>();
	if(GameMode) GameMode->OnGameStateChanged.AddUObject(this, &APSPlayerController::OnGameStateChanged);
}

void APSPlayerController::OnDeath()
{
	ChangeState(NAME_Spectating);
	if(RespawnComponent) RespawnComponent->StartRespawn();
	if(GetGameInstance<UPSGameInstance>()) GetGameInstance<UPSGameInstance>()->OnDeath();
}

void APSPlayerController::OnPauseGame()
{
	SetPause(!IsPaused());
}

void APSPlayerController::OnGameStateChanged(EGameState GameState)
{
	GameState == EGameState::InProgress
		? SetInputMode(FInputModeGameOnly())
		: SetInputMode(FInputModeGameAndUI());

	SetShowMouseCursor(GameState == EGameState::InProgress ? false : true);
}
