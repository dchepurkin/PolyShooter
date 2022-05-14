// PolyShooter By DChepurkin

#pragma once

#include "CoreMinimal.h"
#include "PSAnimNotifyStateBase.h"
#include "PSSetupMagazineAnimNotify.generated.h"

UCLASS()
class POLYSHOOTER_API UPSSetupMagazineAnimNotify : public UPSAnimNotifyStateBase
{
	GENERATED_BODY()

public:
	virtual FString GetNotifyName_Implementation() const override;

protected:
	virtual void OnNotifyBegin(UPSWeaponComponent* WeaponComponent) override;
	virtual void OnNotifyEnd(UPSWeaponComponent* WeaponComponent) override;
};
