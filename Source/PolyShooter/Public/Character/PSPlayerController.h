// PolyShooter By DChepurkin

#pragma once

#include "CoreMinimal.h"
#include "PSRespawnComponent.h"
#include "GameFramework/PlayerController.h"
#include "PSPlayerController.generated.h"

UCLASS()
class POLYSHOOTER_API APSPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	APSPlayerController();

protected:
	virtual void OnPossess(APawn* InPawn) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UPSRespawnComponent* RespawnComponent;

private:
	void OnDeath();
};
