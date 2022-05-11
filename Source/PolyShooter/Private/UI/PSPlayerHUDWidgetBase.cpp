// PolyShooter By DChepurkin

#include "UI/PSPlayerHUDWidgetBase.h"

#include "PSGameInstance.h"
#include "PSHealthComponent.h"
#include "PSWeaponBase.h"
#include "PSWeaponComponent.h"
#include "Components/Image.h"
#include "Components/ProgressBar.h"

DEFINE_LOG_CATEGORY_STATIC(LogPSPlayerHUD, All, All)

void UPSPlayerHUDWidgetBase::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if(const auto Pawn = GetOwningPlayerPawn())
	{
		if(const auto HealthComponent = Pawn->FindComponentByClass<UPSHealthComponent>())
		{
			HealthComponent->OnHealthChanged.AddUObject(this, &UPSPlayerHUDWidgetBase::SetHealthPercent);
		}

		if(const auto WeaponComponent = Pawn->FindComponentByClass<UPSWeaponComponent>())
		{
			WeaponComponent->OnChangeWeapon.AddUObject(this, &UPSPlayerHUDWidgetBase::OnChangeWeapon);
		}
	}
}

void UPSPlayerHUDWidgetBase::SetHealthPercent(const float HealthPercent) const
{
	if(!HealthProgressBar) return;

	HealthProgressBar->SetPercent(HealthPercent);
	HealthProgressBar->SetFillColorAndOpacity(HealthPercent > HealthCriticalThreshold ? GoodColor : BadColor);
}

void UPSPlayerHUDWidgetBase::OnChangeWeapon(APSWeaponBase* CurrentWeapon) const
{
	if(!CrossHairImage || !WeaponImage) return;
	CrossHairImage->SetBrushFromTexture(CurrentWeapon->GetWeaponUIData().CrossHairImage);
	WeaponImage->SetBrushFromTexture(CurrentWeapon->GetWeaponUIData().WeaponImage);
}

void UPSPlayerHUDWidgetBase::GetAmmoData(FAmmoData& AmmoData) const
{
	const auto Pawn = GetOwningPlayerPawn();
	if(!Pawn) return;

	const auto WeaponComponent = Pawn->FindComponentByClass<UPSWeaponComponent>();
	if(!WeaponComponent) return;

	WeaponComponent->GetAmmoData(AmmoData);
}

void UPSPlayerHUDWidgetBase::GetPlayerLifes(int32& Lifes) const
{
	if(!GetOwningPlayer() || !GetOwningPlayer()->GetGameInstance<UPSGameInstance>()) return;

	GetOwningPlayer()->GetGameInstance<UPSGameInstance>()->GetLifes(Lifes);	
}
