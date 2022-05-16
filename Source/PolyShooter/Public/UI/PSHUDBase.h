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
public:
	void ShowQuitGameQuiestion(bool Show);

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=PSHUDBase)
	TMap<EGameState, TSubclassOf<UPSWidgetBase>> StateWidgetsClasses;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=PSHUDBase)
	TSubclassOf<UPSWidgetBase> QuitGameQuestionWidgetClass;

	virtual void BeginPlay() override;

private:	
	UPROPERTY()
	TMap<EGameState, UPSWidgetBase*> Widgets;

	UPROPERTY()
	UPSWidgetBase* CurrentWidget;

	void OnGameStateChanged(EGameState GameState);
	void CreateSubWidget(TSubclassOf<UPSWidgetBase> WidgetClass);
};
