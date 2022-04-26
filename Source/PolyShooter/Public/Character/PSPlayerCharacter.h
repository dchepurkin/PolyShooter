// PolyShooter By DChepurkin

#pragma once

#include "CoreMinimal.h"
#include "Character/PSCharacterBase.h"
#include "PSPlayerCharacter.generated.h"

class UCameraComponent;

UCLASS()
class POLYSHOOTER_API APSPlayerCharacter : public APSCharacterBase
{
	GENERATED_BODY()

public:
	APSPlayerCharacter(const FObjectInitializer& ObjectInitializer);

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category=Components)
	UCameraComponent* CameraComponent;

	virtual void BeginPlay() override;

private:
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
};
