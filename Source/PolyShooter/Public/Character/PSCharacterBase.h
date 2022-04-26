// PolyShooter By DChepurkin

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PSCharacterBase.generated.h"

UCLASS()
class POLYSHOOTER_API APSCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	APSCharacterBase(const FObjectInitializer& ObjectInitializer);

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;

};
