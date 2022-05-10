// PolyShooter By DChepurkin

#pragma once

#include "CoreMinimal.h"
#include "Environments/PSDoorBase.h"
#include "PSHorizontalDoubleDoor.generated.h"

UCLASS()
class POLYSHOOTER_API APSHorizontalDoubleDoor : public APSDoorBase
{
	GENERATED_BODY()

public:
	APSHorizontalDoubleDoor();
	virtual void BeginPlay() override;

protected:
	virtual void OnTimelineTick(float Alpha) override;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category=PSDoor)
	UStaticMeshComponent* LeftDoorStaticMesh;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category=PSDoor)
	UStaticMeshComponent* RightDoorStaticMesh;

private:
	FVector LeftDoorClosePosition;
	FVector LeftDoorOpenPosition;
	FVector RightDoorClosePosition;
	FVector RightDoorOpenPosition;
	
};
