// PolyShooter By DChepurkin

#pragma once

#include "CoreMinimal.h"
#include "Components/SplineComponent.h"
#include "GameFramework/Actor.h"
#include "PSRoute.generated.h"

class USplineComponent;

UCLASS()
class POLYSHOOTER_API APSRoute : public AActor
{
	GENERATED_BODY()

public:
	APSRoute();

	FVector GetPointLocation(const int32& PointIndex) const;
	int32 GetPointsNum() const { return SplineComponent->GetNumberOfSplinePoints(); }

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=PSRoute)
	USplineComponent* SplineComponent;
};
