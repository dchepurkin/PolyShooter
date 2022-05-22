// PolyShooter By DChepurkin

#pragma once

#include "CoreMinimal.h"
#include "UI/PSWidgetBase.h"
#include "PSLoadingScreenWidget.generated.h"

class UImage;

UCLASS()
class POLYSHOOTER_API UPSLoadingScreenWidget : public UPSWidgetBase
{
	GENERATED_BODY()

protected:
	virtual void NativeOnInitialized() override;
	
	UPROPERTY(meta=(BindWidget))
	UImage* BackgroundImage;

private:
	void SetBackgroundImage();
};
