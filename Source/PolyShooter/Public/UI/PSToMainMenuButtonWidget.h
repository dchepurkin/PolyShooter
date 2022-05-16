// PolyShooter By DChepurkin

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PSToMainMenuButtonWidget.generated.h"

class UButton;

UCLASS()
class POLYSHOOTER_API UPSToMainMenuButtonWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeOnInitialized() override;

	UPROPERTY(meta=(BindWidget))
	UButton* ToMainMenuButton;

private:
	UFUNCTION()
	void OnToMainMenu();
};
