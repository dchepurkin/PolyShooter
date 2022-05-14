// PolyShooter By DChepurkin

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "PSHUDMenu.generated.h"

class UPSWidgetBase;

UCLASS()
class POLYSHOOTER_API APSHUDMenu : public AHUD
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=PSHUDMenu)
	TSubclassOf<UPSWidgetBase> MainMenuWidgetClass;
};
