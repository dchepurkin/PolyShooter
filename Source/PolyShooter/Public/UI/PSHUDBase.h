// PolyShooter By DChepurkin

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "PSCoreTypes.h"
#include "PSHUDBase.generated.h"

class UPSWidgetBase;

DECLARE_MULTICAST_DELEGATE(FOnLoadingScreenFinishedSignature)

UCLASS()
class POLYSHOOTER_API APSHUDBase : public AHUD
{
	GENERATED_BODY()

public:
	APSHUDBase();
	
	void ShowLoadingScreen();
	FOnLoadingScreenFinishedSignature OnLoadingScreenFinished;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="PSHUD|LoadingScreen")
	TSubclassOf<UPSWidgetBase> LoadingScreenWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="PSHUD|LoadingScreen", meta=(ClampMin = "0.0"))
	float LoadingScreenDelay = 3.0f;

	void CreateSubWidget(TSubclassOf<UPSWidgetBase> WidgetClass);

private:
	FTimerHandle LoadingScreenTimer;

	void OnLoadingScreenTimer();
};
