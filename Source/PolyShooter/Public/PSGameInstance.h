// PolyShooter By DChepurkin

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "PSCoreTypes.h"
#include "PSGameInstance.generated.h"

UCLASS()
class POLYSHOOTER_API UPSGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	void OnDeath();
	void SetPlayerLifes(const int32 NewLifeAmount);
	void SaveAmmoData(const TMap<TSubclassOf<APSWeaponBase>, FAmmoData>& PlayerAmmoData);

	UFUNCTION(BlueprintCallable)
	int32 GetLifes() const { return PlayerData.Lifes; }

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=PSGameInstance)
	FPlayerData PlayerData;

private:
};
