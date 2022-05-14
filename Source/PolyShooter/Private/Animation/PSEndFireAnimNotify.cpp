// PolyShooter By DChepurkin

#include "Animation/PSEndFireAnimNotify.h"

#include "PSWeaponComponent.h"

FString UPSEndFireAnimNotify::GetNotifyName_Implementation() const
{
	FString NotifyName = "Fire Finished";
	return NotifyName;
}

void UPSEndFireAnimNotify::OnNotifyEnd(UPSWeaponComponent* WeaponComponent)
{
	if(WeaponComponent) WeaponComponent->OnEndFireAnim();
}
