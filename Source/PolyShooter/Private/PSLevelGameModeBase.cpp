// PolyShooter By DChepurkin

#include "PSLevelGameModeBase.h"

#include "EngineUtils.h"
#include "PSAICharacter.h"
#include "PSHealthComponent.h"
#include "PSPlayerCharacter.h"
#include "PSPlayerController.h"
#include "PSWeaponComponent.h"
#include "Kismet/GameplayStatics.h"
#include "UI/PSHUDBase.h"

APSLevelGameModeBase::APSLevelGameModeBase()
{
	DefaultPawnClass = APSPlayerCharacter::StaticClass();
	PlayerControllerClass = APSPlayerController::StaticClass();
	HUDClass = APSHUDBase::StaticClass();
}

void APSLevelGameModeBase::StartPlay()
{
	Super::StartPlay();
	SetGameState(EGameState::InProgress);

	BotsNum = GetBOTs().Num();
}

TArray<AActor*> APSLevelGameModeBase::GetBOTs() const
{
	TArray<AActor*> ResultArray;

	if(GetWorld())
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), APSAICharacter::StaticClass(), ResultArray);

	return ResultArray;
}

void APSLevelGameModeBase::OnBotDead()
{
	if(!--BotsNum) OnLevenClean.Broadcast();	
}

void APSLevelGameModeBase::RespawnPlayer(AController* Controller)
{
	if(!Controller) return;
	RestartPlayer(Controller);
}

void APSLevelGameModeBase::SetGameState(const EGameState NewGameState)
{
	GameState = NewGameState;
	OnGameStateChanged.Broadcast(GameState);
}

void APSLevelGameModeBase::GameOver()
{
	for(const auto Pawn : TActorRange<APawn>(GetWorld()))
	{
		if(!Pawn) continue;
		Pawn->TurnOff();
		Pawn->DisableInput(nullptr);
	}
	SetGameState(EGameState::GameOver);
}
