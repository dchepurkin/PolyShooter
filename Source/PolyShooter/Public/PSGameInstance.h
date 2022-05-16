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
	void SaveAmmoData(const TMap<TSubclassOf<APSWeaponBase>, FAmmoData>& PlayerAmmoData);
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
	/*UFUNCTION()
	void BeginLoadingScreen(const FString& MapName);*/

	UFUNCTION()
	void OnOpenLevel(UWorld* World);
};
