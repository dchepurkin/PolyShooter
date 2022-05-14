// PolyShooter By DChepurkin


#include "Animation/PSReloadAnimNotify.h"

#include "PSWeaponComponent.h"

FString UPSReloadAnimNotify::GetNotifyName_Implementation() const
{
	FString NotifyName = "Reload";
	return NotifyName;
}

void UPSReloadAnimNotify::OnNotifyBegin(UPSWeaponComponent* WeaponComponent)
{
	if(WeaponComponent) WeaponComponent->OnReloadStarted();
}

void UPSReloadAnimNotify::OnNotifyEnd(UPSWeaponComponent* WeaponComponent)
{
	if(WeaponComponent) WeaponComponent->OnReloadFinished();
}


