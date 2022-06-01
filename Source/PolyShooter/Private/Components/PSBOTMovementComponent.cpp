// PolyShooter By DChepurkin

#include "Components/PSBOTMovementComponent.h"

#include "PSRoute.h"

DEFINE_LOG_CATEGORY_STATIC(LogBOTMovement, All, All);

void UPSBOTMovementComponent::BeginPlay()
{
	Super::BeginPlay();

	if(RouteInstance) CurrentRoutePoint = FMath::RandRange(0, RouteInstance->GetPointsNum());
}
