// PolyShooter By DChepurkin

#pragma once

#include "CoreMinimal.h"
#include "Character/PSCharacterBase.h"
#include "PSAICharacter.generated.h"

class UWidgetComponent;

UCLASS()
class POLYSHOOTER_API APSAICharacter : public APSCharacterBase
{
	GENERATED_BODY()

public:
	APSAICharacter(const FObjectInitializer& ObjectInitializer);
	virtual void BeginPlay() override;

protected:
	virtual void OnDeath() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=Components)
	UWidgetComponent* HealthBar;

private:
	void InitHealhBar();
};
