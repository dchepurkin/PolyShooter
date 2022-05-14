// PolyShooter By DChepurkin

#include "Animation/PSSetupMagazineAnimNotify.h"

#include "PSWeaponComponent.h"

FString UPSSetupMagazineAnimNotify::GetNotifyName_Implementation() const
{
	FString NotifyName = "Setup Magazine";
	return NotifyName;
}

void UPSSetupMagazineAnimNotify::OnNotifyBegin(UPSWeaponComponent* WeaponComponent)
{
	if(WeaponComponent) WeaponComponent->OnStartSetupMagazine();
}

void UPSSetupMagazineAnimNotify::OnNotifyEnd(UPSWeaponComponent* WeaponComponent)
{
	if(WeaponComponent) WeaponComponent->OnEndSetupMagazine();
}
