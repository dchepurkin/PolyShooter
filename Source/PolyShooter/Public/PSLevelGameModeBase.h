// PolyShooter By DChepurkin

#pragma once

#include "CoreMinimal.h"
#include "PSCoreTypes.h"
#include "PSGameModeBase.h"
#include "PSLevelGameModeBase.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnGameStateChangedSignature, EGameState)
DECLARE_MULTICAST_DELEGATE(FOnLevenClean);

UCLASS()
class POLYSHOOTER_API APSLevelGameModeBase : public APSGameModeBase
{
	GENERATED_BODY()

public:
	FOnGameStateChangedSignature OnGameStateChanged;
	FOnLevenClean OnLevenClean;

	APSLevelGameModeBase();
	virtual void StartPlay() override;

	int32 GetBotsNum() const { return BotsNum; }
	void OnBotDead();
	bool CanExitLevel() const { return !BotsNum; }

	void RespawnPlayer(AController* Controller);
	const EGameState& GetGameState() const { return GameState; }
	void SetGameState(const EGameState NewGameState);
	void GameOver();

private:
	EGameState GameState = EGameState::InProgress;
	int32 BotsNum = 0;

	TArray<AActor*> GetBOTs() const;
};
