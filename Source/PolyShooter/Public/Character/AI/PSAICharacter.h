// PolyShooter By DChepurkin

#pragma once

#include "CoreMinimal.h"
#include "Character/PSCharacterBase.h"
#include "PSAICharacter.generated.h"

UCLASS()
class POLYSHOOTER_API APSAICharacter : public APSCharacterBase
{
	GENERATED_BODY()

public:
	APSAICharacter(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void OnDeath() override;
};
