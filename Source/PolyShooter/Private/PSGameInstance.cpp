// PolyShooter By DChepurkin

#include "PSGameInstance.h"

#include "PSWeaponBase.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY_STATIC(LogPSGameInstance, All, All);

void UPSGameInstance::OnDeath()
{
	SetPlayerLifes(PlayerData.Lifes - 1);
}

void UPSGameInstance::SetPlayerLifes(const int32 NewLifeAmount)
{
	PlayerData.Lifes = FMath::Clamp(NewLifeAmount, 0, PlayerData.MaxLifes);
}

void UPSGameInstance::SaveAmmoData(const TMap<TSubclassOf<APSWeaponBase>, FAmmoData>& PlayerAmmoData) {}
