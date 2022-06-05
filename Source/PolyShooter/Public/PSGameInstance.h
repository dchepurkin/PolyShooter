// PolyShooter By DChepurkin

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "PSCoreTypes.h"
#include "PSGameInstance.generated.h"

class UUserWidget;

UCLASS()
class POLYSHOOTER_API UPSGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	virtual void Init() override;

	void OnDeath();
	void SetPlayerLifes(const int32 NewLifeAmount);
	void StartGame();

	UFUNCTION(BlueprintCallable)
	int32 GetLifes() const { return CurrentLifes; }

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=PSGameInstance)
	FPlayerData PlayerData;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=PSGameInstance, meta=(ClampMin = "0.0"))
	float StartLevelCameraFadeOutDuration = 5.0f;

private:
	int32 CurrentLifes = 0;
	TMap<TSubclassOf<APSWeaponBase>, FAmmoData> Weapons;
	
	UFUNCTION()
	void PreOpenLevel(const FString& MapName);

	UFUNCTION()
	void OnOpenLevel(UWorld* World);

	void SaveWeaponInfo();
	void LoadWeaponInfo();
};


