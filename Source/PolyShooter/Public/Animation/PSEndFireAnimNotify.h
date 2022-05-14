// PolyShooter By DChepurkin

#pragma once

#include "CoreMinimal.h"
#include "PSAnimNotifyStateBase.h"
#include "PSEndFireAnimNotify.generated.h"

UCLASS()
class POLYSHOOTER_API UPSEndFireAnimNotify : public UPSAnimNotifyStateBase
{
	GENERATED_BODY()

public:
	virtual FString GetNotifyName_Implementation() const override;
	
protected:
	virtual void OnNotifyEnd(UPSWeaponComponent* WeaponComponent) override;
};
