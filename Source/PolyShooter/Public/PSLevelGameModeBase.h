// PolyShooter By DChepurkin

#pragma once

#include "CoreMinimal.h"
#include "PSCoreTypes.h"
#include "PSGameModeBase.h"
#include "PSLevelGameModeBase.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnGameStateChangedSignature, EGameState)

UCLASS()
class POLYSHOOTER_API APSLevelGameModeBase : public APSGameModeBase
{
	GENERATED_BODY()

public:
	APSLevelGameModeBase();
	virtual void StartPlay() override;

	FOnGameStateChangedSignature OnGameStateChanged;

	void RespawnPlayer(AController* Controller);
	const EGameState& GetGameState() const { return GameState; }
	void SetGameState(const EGameState NewGameState);
	void GameOver();

private:
	EGameState GameState = EGameState::InProgress;
};
