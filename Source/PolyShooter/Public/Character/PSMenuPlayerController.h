// PolyShooter By DChepurkin

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PSMenuPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class POLYSHOOTER_API APSMenuPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
};
