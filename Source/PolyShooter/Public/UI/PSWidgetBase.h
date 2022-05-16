// PolyShooter By DChepurkin

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PSWidgetBase.generated.h"

class UWidgetAnimation;

UCLASS()
class POLYSHOOTER_API UPSWidgetBase : public UUserWidget
{
	GENERATED_BODY()

public:
	void Show();
	
protected:
	UPROPERTY(Transient, meta=(BindWidgetAnim))
	UWidgetAnimation* ShowAnimation;
};
