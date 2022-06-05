// PolyShooter By DChepurkin

#pragma once

#include "CoreMinimal.h"
#include "Pickup/PSPickupBase.h"
#include "PSHealthPickup.generated.h"

/**
 * 
 */
UCLASS()
class POLYSHOOTER_API APSHealthPickup : public APSPickupBase
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=PSPickup)
	float HealthAmount = 50.0f;

	virtual bool CanTake(AActor* OtherActor) override;
	virtual void TakePickup(AActor* OtherActor) override;
};
