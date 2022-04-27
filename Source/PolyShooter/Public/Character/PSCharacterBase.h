// PolyShooter By DChepurkin

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PSCharacterBase.generated.h"

class UPSHealthComponent;

UCLASS()
class POLYSHOOTER_API APSCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	APSCharacterBase(const FObjectInitializer& ObjectInitializer);

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=Components)
	UPSHealthComponent* HealthComponent;

protected:
	virtual void BeginPlay() override;
	
	void OnDeath();
};
