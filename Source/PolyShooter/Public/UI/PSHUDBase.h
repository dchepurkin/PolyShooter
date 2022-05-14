// PolyShooter By DChepurkin

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "PSCoreTypes.h"
#include "PSHUDBase.generated.h"

class UPSWidgetBase;

UCLASS()
class POLYSHOOTER_API APSHUDBase : public AHUD
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=PSHUDBase)
	TSubclassOf<UPSWidgetBase> PlayerHUDWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=PSHUDBase)
	TSubclassOf<UPSWidgetBase> PauseWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=PSHUDBase)
	TSubclassOf<UPSWidgetBase> GameOverWidgetClass;

	virtual void BeginPlay() override;
	
private:
	UPROPERTY()
	TMap<EGameState, UPSWidgetBase*> Widgets;

	UPROPERTY()
	UPSWidgetBase* CurrentWidget;

	void OnGameStateChanged(EGameState GameState);
};
