// PolyShooter By DChepurkin

#pragma once

#include "CoreMinimal.h"
#include "UI/PSWidgetBase.h"
#include "PSPauseWidget.generated.h"

class UButton;

UCLASS()
class POLYSHOOTER_API UPSPauseWidget : public UPSWidgetBase
{
	GENERATED_BODY()

protected:
	virtual void NativeOnInitialized() override;

	UPROPERTY(meta=(BindWidget))
	UButton* ResumeGameButton;

private:
	UFUNCTION()
	void OnResumeGame();
};
