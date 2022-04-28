// PolyShooter By DChepurkin

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PSPlayerMovementComponent.generated.h"

UCLASS()
class POLYSHOOTER_API UPSPlayerMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()

public:
	virtual float GetMaxSpeed() const override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=PSPlayerMovementComponent, meta=(ClampMin = "1.0"))
	float RunSpeedModifier = 2.0f;
};
