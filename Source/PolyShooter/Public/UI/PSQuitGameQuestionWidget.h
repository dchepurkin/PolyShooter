// PolyShooter By DChepurkin

#pragma once

#include "CoreMinimal.h"
#include "UI/PSWidgetBase.h"
#include "PSQuitGameQuestionWidget.generated.h"

class APSLevelGameModeBase;
class UButton;

UCLASS()
class POLYSHOOTER_API UPSQuitGameQuestionWidget : public UPSWidgetBase
{
	GENERATED_BODY()

protected:
	virtual void NativeOnInitialized() override;

	UPROPERTY(meta=(BindWidget))
	UButton* YesButton;

	UPROPERTY(meta=(BindWidget))
	UButton* NoButton;

private:
	UFUNCTION()
	void OnYes();

	UFUNCTION()
	void OnNo();
};
