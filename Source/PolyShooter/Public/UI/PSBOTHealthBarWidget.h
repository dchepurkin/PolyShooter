// PolyShooter By DChepurkin

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PSBOTHealthBarWidget.generated.h"

class UProgressBar;

UCLASS()
class POLYSHOOTER_API UPSBOTHealthBarWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetOwnerPawn(APawn* NewOwnerPawn);

protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UPROPERTY(meta=(BindWidget))
	UProgressBar* HealthProgressBar;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=PSBOTHealthBar)
	FLinearColor GoodColor = {0.05098f, 0.05098f, 0.05098f};

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=PSBOTHealthBar)
	FLinearColor BadColor = FLinearColor::Red;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=PSBOTHealthBar, meta=(ClampMin = "1000.0"))
	float VisibleDistance = 2000.0f;

private:
	UPROPERTY()
	APawn* OwnerPawn = nullptr;

	void SetHealthPercent(const float HealthPercent);
	void UpdateVisibility();
	void OnDeath() { SetVisibility(ESlateVisibility::Hidden); }

	bool IsInVisibleDistance();
	bool IsPlayerVisible();
};
