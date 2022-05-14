// PolyShooter By DChepurkin

#pragma once

#include "CoreMinimal.h"
#include "PSWidgetBase.h"
#include "PSMainMenuWidget.generated.h"

class UButton;

UCLASS()
class POLYSHOOTER_API UPSMainMenuWidget : public UPSWidgetBase
{
	GENERATED_BODY()

protected:
	virtual void NativeOnInitialized() override;

	UPROPERTY(meta=(BindWidget))
	UButton* QuitGameButton;

private:
	UFUNCTION()
	void OnQuitGame();
};
