// PolyShooter By DChepurkin

#pragma once

#include "CoreMinimal.h"
#include "PSCoreTypes.h"
#include "PSRespawnComponent.h"
#include "GameFramework/PlayerController.h"
#include "PSPlayerController.generated.h"

UCLASS()
class POLYSHOOTER_API APSPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	APSPlayerController();
	virtual bool SetPause(bool bPause, FCanUnpause CanUnpauseDelegate = FCanUnpause()) override;

protected:
	virtual void OnPossess(APawn* InPawn) override;
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UPSRespawnComponent* RespawnComponent;

private:
	void OnDeath();
	void OnPauseGame();
	void OnGameStateChanged(EGameState GameState);
};
