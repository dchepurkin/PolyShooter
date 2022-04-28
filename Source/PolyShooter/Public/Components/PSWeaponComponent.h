// PolyShooter By DChepurkin

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PSWeaponComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class POLYSHOOTER_API UPSWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPSWeaponComponent();

protected:
	virtual void BeginPlay() override;
};
