// PolyShooter By DChepurkin

#pragma once

#include "CoreMinimal.h"
#include "UI/PSHUDBase.h"
#include "PSHUDLevel.generated.h"

UCLASS()
class POLYSHOOTER_API APSHUDLevel : public APSHUDBase
{
	GENERATED_BODY()

public:
	void ShowQuitGameQuiestion(bool Show);

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=PSHUD)
	TArray<FWidgetsData> StateWidgetsData;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=PSHUD)
	TSubclassOf<UPSWidgetBase> QuitGameQuestionWidgetClass;

private:
	UPROPERTY()
	TMap<EGameState, UPSWidgetBase*> Widgets;

	UPROPERTY()
	UPSWidgetBase* CurrentWidget;

	void OnGameStateChanged(EGameState GameState);
};
