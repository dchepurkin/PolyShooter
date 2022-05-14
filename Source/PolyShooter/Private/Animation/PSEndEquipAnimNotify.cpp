// PolyShooter By DChepurkin

#include "Animation/PSEndEquipAnimNotify.h"
#include "PSWeaponComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogPSEndEquipAnimNotify, All, All)

FString UPSEndEquipAnimNotify::GetNotifyName_Implementation() const
{
	FString NotiFyName = "Finish Equip";
	return NotiFyName;
}

void UPSEndEquipAnimNotify::OnNotifyEnd(UPSWeaponComponent* WeaponComponent)
{
	if(WeaponComponent) WeaponComponent->OnEquipFinished();
}
