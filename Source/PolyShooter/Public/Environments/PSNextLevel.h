// PolyShooter By DChepurkin

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PSNextLevel.generated.h"

class UBoxComponent;

UCLASS()
class POLYSHOOTER_API APSNextLevel : public AActor
{
	GENERATED_BODY()

public:
	APSNextLevel();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Component)
	UBoxComponent* NextLevelTrigger;

private:
	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	               const FHitResult& SweepResult);
};
