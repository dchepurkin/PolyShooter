// PolyShooter By DChepurkin

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PSCoreTypes.h"
#include "PSPlayerHUDWidgetBase.generated.h"

class APSWeaponBase;
class UProgressBar;
class UTextBlock;
class UImage;

UCLASS()
class POLYSHOOTER_API UPSPlayerHUDWidgetBase : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void GetAmmoData(FAmmoData& AmmoData) const;

	UFUNCTION(BlueprintCallable)
	bool IsSpectating() const;

	UFUNCTION(BlueprintCallable)
	float GetRespawnCountDown() const;

	UFUNCTION(BlueprintCallable)
	int32 GetPlayerLifes() const;

	UFUNCTION(BlueprintCallable)
	float GetPlayerHealthPercent() const;

	UFUNCTION(BlueprintCallable)
	void GetWeaponUIData(FWeaponUIData& WeaponUIData) const;

protected:
	virtual void NativeOnInitialized() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=PSPlayerHUD)
	FLinearColor GoodColor = FLinearColor(0.05098f, 0.05098f, 0.05098f);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=PSPlayerHUD)
	FLinearColor BadColor = FLinearColor::Red;

	UPROPERTY(meta=(BindWidget))
	UProgressBar* HealthProgressBar;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* PlayerLifesTextBlock;

private:
	void OnPawnChanged(APawn* NewPawn);
	void OnHealthChanged(const float HealthPercent);	
	void UpdateHealthBar();
};
