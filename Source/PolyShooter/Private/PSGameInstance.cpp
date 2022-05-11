// PolyShooter By DChepurkin

#include "PSGameInstance.h"

#include "PSWeaponBase.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY_STATIC(LogPSGameInstance, All, All);


void UPSGameInstance::OnDeath()
{
	--PlayerData.Lifes;
}

void UPSGameInstance::SaveAmmoData(const TMap<TSubclassOf<APSWeaponBase>, FAmmoData>& PlayerAmmoData)
{

}
