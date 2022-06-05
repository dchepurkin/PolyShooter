// PolyShooter By DChepurkin

#pragma once

#include "CoreMinimal.h"
#include "Environments/PSHorizontalDoubleDoor.h"
#include "PSExitLevelDoor.generated.h"

UCLASS()
class POLYSHOOTER_API APSExitLevelDoor : public APSHorizontalDoubleDoor
{
	GENERATED_BODY()

protected:
	virtual void Open() const override;

private:
	bool CanExitLevel() const;
};
