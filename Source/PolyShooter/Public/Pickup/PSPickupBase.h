// PolyShooter By DChepurkin

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PSPickupBase.generated.h"

class USphereComponent;
class USoundCue;

UCLASS()
class POLYSHOOTER_API APSPickupBase : public AActor
{
	GENERATED_BODY()

public:
	APSPickupBase();
	virtual void Tick(float DeltaTime) override;

	static FVector GetSpawnLocationSnapedToFloor(const UWorld* World, const FVector& SpawnLocation);

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=PSPickup)
	USphereComponent* PickupCollision;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=PSPickup)
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=PSPickup)
	USoundCue* TakeSound = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=PSPickup, meta=(ClampMin = "0.0"))
	float MinRotationSpeed = 3.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=PSPickup, meta=(ClampMin = "0.0"))
	float MaxRotationSpeed = 8.0f;

	virtual void TakePickup(AActor* OtherActor);
	virtual bool CanTake(AActor* OtherActor);

private:
	FRotator DeltaRotation;

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	                    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	                    const FHitResult& SweepResult);
};
