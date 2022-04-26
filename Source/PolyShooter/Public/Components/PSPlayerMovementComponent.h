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
	void MoveForward(float AxisValue) const;
	void MoveRight(float AxisValue) const;
};
