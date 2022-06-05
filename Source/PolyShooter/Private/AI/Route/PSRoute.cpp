// PolyShooter By DChepurkin

#include "AI/Route/PSRoute.h"

#include "Components/SplineComponent.h"

APSRoute::APSRoute()
{
	PrimaryActorTick.bCanEverTick = false;

	SplineComponent = CreateDefaultSubobject<USplineComponent>("SplineComponent");
	SplineComponent->SetSplinePointType(0, ESplinePointType::Linear);
	SplineComponent->SetClosedLoop(true);
}

FVector APSRoute::GetPointLocation(const int32& PointIndex) const
{
	return SplineComponent->GetLocationAtSplinePoint(PointIndex, ESplineCoordinateSpace::World);
}

void APSRoute::BeginPlay()
{
	Super::BeginPlay();
}
