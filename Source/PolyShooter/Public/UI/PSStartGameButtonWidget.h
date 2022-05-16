// PolyShooter By DChepurkin

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PSStartGameButtonWidget.generated.h"

class UButton;

UCLASS()
class POLYSHOOTER_API UPSStartGameButtonWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeOnInitialized() override;

	UPROPERTY(meta=(BindWidget))
	UButton* StartGameButton;

private:
	UFUNCTION()
	void OnStartGame();
};
