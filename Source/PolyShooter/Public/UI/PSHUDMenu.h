// PolyShooter By DChepurkin

#pragma once

#include "CoreMinimal.h"
#include "PSHUDBase.h"
#include "PSHUDMenu.generated.h"

class UPSWidgetBase;

UCLASS()
class POLYSHOOTER_API APSHUDMenu : public APSHUDBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=PSHUD)
	TSubclassOf<UPSWidgetBase> MainMenuWidgetClass;
};
