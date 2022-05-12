// PolyShooter By DChepurkin

#include "UI/PSPlayerHUDWidgetBase.h"

#include "PSGameInstance.h"
#include "PSHealthComponent.h"
#include "PSRespawnComponent.h"
#include "PSWeaponBase.h"
#include "PSWeaponComponent.h"
#include "Components/Image.h"
#include "Components/ProgressBar.h"

DEFINE_LOG_CATEGORY_STATIC(LogPSPlayerHUD, All, All)

void UPSPlayerHUDWidgetBase::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	if(GetOwningPlayer())
	{
		GetOwningPlayer()->GetOnNewPawnNotifier().AddUObject(this, &UPSPlayerHUDWidgetBase::OnPawnChanged);
		OnPawnChanged(GetOwningPlayerPawn());
	}
}

void UPSPlayerHUDWidgetBase::OnPawnChanged(APawn* NewPawn)
{
	if(!NewPawn) return;

	if(const auto HealthComponent = NewPawn->FindComponentByClass<UPSHealthComponent>())
	{
		HealthComponent->OnHealthChanged.AddUObject(this, &UPSPlayerHUDWidgetBase::OnHealthChanged);
	}
	UpdateHealthBar();
}

void UPSPlayerHUDWidgetBase::OnHealthChanged(const float HealthPercent)
{
	if(!HealthProgressBar) return;

	UpdateHealthBar();
}

void UPSPlayerHUDWidgetBase::GetWeaponUIData(FWeaponUIData& WeaponUIData) const
{
	if(!GetOwningPlayerPawn()) return;

	const auto WeaponComponent = GetOwningPlayerPawn()->FindComponentByClass<UPSWeaponComponent>();
	if(!WeaponComponent) return;

	WeaponComponent->GetUIData(WeaponUIData);
}

void UPSPlayerHUDWidgetBase::UpdateHealthBar()
{
	const auto HealthProgressBarColor = FMath::Lerp(BadColor, GoodColor, GetPlayerHealthPercent());
	HealthProgressBar->SetFillColorAndOpacity(HealthProgressBarColor);
}

void UPSPlayerHUDWidgetBase::GetAmmoData(FAmmoData& AmmoData) const
{
	if(!GetOwningPlayerPawn()) return;

	const auto WeaponComponent = GetOwningPlayerPawn()->FindComponentByClass<UPSWeaponComponent>();
	if(!WeaponComponent) return;

	WeaponComponent->GetAmmoData(AmmoData);
}

bool UPSPlayerHUDWidgetBase::IsSpectating() const
{
	return GetOwningPlayer() && GetOwningPlayer()->StateName == NAME_Spectating;
}

float UPSPlayerHUDWidgetBase::GetRespawnCountDown() const
{
	if(!GetOwningPlayer()) return 0.0f;

	const auto RespawnComponent = GetOwningPlayer()->FindComponentByClass<UPSRespawnComponent>();
	if(!RespawnComponent) return 0.0f;

	return RespawnComponent->GetRespawnCountDown();
}

int32 UPSPlayerHUDWidgetBase::GetPlayerLifes() const
{
	if(!GetOwningPlayer() || !GetOwningPlayer()->GetGameInstance<UPSGameInstance>()) return 0;

	return GetOwningPlayer()->GetGameInstance<UPSGameInstance>()->GetLifes();
}

float UPSPlayerHUDWidgetBase::GetPlayerHealthPercent() const
{
	if(!GetOwningPlayerPawn()) return 0.0f;

	const auto HealthComponent = GetOwningPlayerPawn()->FindComponentByClass<UPSHealthComponent>();
	if(!HealthComponent) return 0.0f;

	return HealthComponent->GetHealthPercent();
}
