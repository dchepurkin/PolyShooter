// PolyShooter By DChepurkin

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PSBOTMovementComponent.generated.h"

class APSRoute;

UCLASS()
class POLYSHOOTER_API UPSBOTMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()

public:
	const FVector& GetPointLocation(const int32& PointIndex) const;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category=PSCharacter)
	APSRoute* RouteInstance;

private:
	int32 CurrentRoutePoint = 0;
};
