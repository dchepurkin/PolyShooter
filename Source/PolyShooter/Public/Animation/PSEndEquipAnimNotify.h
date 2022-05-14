// PolyShooter By DChepurkin

#pragma once

#include "CoreMinimal.h"
#include "PSAnimNotifyStateBase.h"
#include "PSEndEquipAnimNotify.generated.h"

class UPSWeaponComponent;

UCLASS()
class POLYSHOOTER_API UPSEndEquipAnimNotify : public UPSAnimNotifyStateBase
{
	GENERATED_BODY()

public:
	virtual FString GetNotifyName_Implementation() const override;

protected:
	virtual void OnNotifyEnd(UPSWeaponComponent* WeaponComponent) override;

};
