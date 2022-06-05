// PolyShooter By DChepurkin

#pragma once

#include "CoreMinimal.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Actor.h"
#include "PSDoorBase.generated.h"

class USoundCue;
class UTimelineComponent;
class UBoxComponent;
class UCurveFloat;

UCLASS()
class POLYSHOOTER_API APSDoorBase : public AActor
{
	GENERATED_BODY()

public:
	APSDoorBase();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=PSDoor)
	UBoxComponent* TriggerCollision;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=PSDoor)
	UStaticMeshComponent* DoorArchStaticMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=PSDoor)
	UTimelineComponent* OpenDoorTimeline;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=PSDoor, meta=(EditCondition = "!CantOpen"))
	UCurveFloat* OpenDoorCurve;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=PSDoor, meta=(ClampMin = "0.0", EditCondition = "!CantOpen"))
	float OpenDoorSpace = 300.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=PSDoor, meta=(ClampMin = "0.0", EditCondition = "!CantOpen"))
	float CloseDoorDelay = 1.5f;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category=PSDoor)
	bool CantOpen = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=PSDoor, meta=(EditCondition = "!CantOpen"))
	USoundCue* OpenDoorSound = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=PSDoor, meta=(EditCondition = "!CantOpen"))
	USoundCue* CloseDoorSound = nullptr;

	UFUNCTION()
	virtual void OnTimelineTick(float Alpha) { IsOpen = FMath::IsNearlyEqual(Alpha, 1.0f); }

	virtual void Open() const;

private:
	FTimerHandle CloseDoorTimerHandle;
	FOnTimelineFloat UpdateTimelineFloat;

	bool IsOpen = false;

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	                    const FHitResult& SweepResult);

	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
	void Close() const;
};
