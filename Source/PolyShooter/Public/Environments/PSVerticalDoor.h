// PolyShooter By DChepurkin

#pragma once

#include "CoreMinimal.h"
#include "Environments/PSDoorBase.h"
#include "PSVerticalDoor.generated.h"

UCLASS()
class POLYSHOOTER_API APSVerticalDoor : public APSDoorBase
{
	GENERATED_BODY()

public:
	APSVerticalDoor();
	virtual void BeginPlay() override;

protected:
	virtual void OnTimelineTick(float Alpha) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=PSDoor)
	UStaticMeshComponent* DoorStaticMesh;

private:
	FVector ClosePosition;
	FVector OpenPosition;
};
