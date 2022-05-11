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
	void GetPlayerLifes(int32& Lifes) const;

protected:
	virtual void NativeOnInitialized() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=PSPlayerHUD,meta=(ClampMin = "0.1", ClampMax = "0.9"))
	float HealthCriticalThreshold = 0.3;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=PSPlayerHUD)
	FLinearColor GoodColor = FLinearColor(0.05098f, 0.05098f, 0.05098f);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=PSPlayerHUD)
	FLinearColor BadColor = FLinearColor::Red;

	UPROPERTY(meta=(BindWidget))
	UProgressBar* HealthProgressBar;

	UPROPERTY(meta=(BindWidget))
	UImage* CrossHairImage;

	UPROPERTY(meta=(BindWidget))
	UImage* WeaponImage;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* PlayerLifesTextBlock;

private:
	void SetHealthPercent(const float HealthPercent) const;
	void OnChangeWeapon(APSWeaponBase* CurrentWeapon) const;
};
