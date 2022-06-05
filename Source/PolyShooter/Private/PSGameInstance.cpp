// PolyShooter By DChepurkin

#include "PSGameInstance.h"

#include "PSPlayerCharacter.h"
#include "PSUtils.h"
#include "PSWeaponBase.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY_STATIC(LogPSGameInstance, All, All);

void UPSGameInstance::Init()
{
	Super::Init();

	FCoreUObjectDelegates::PreLoadMap.AddUObject(this, &UPSGameInstance::PreOpenLevel);
	FCoreUObjectDelegates::PostLoadMapWithWorld.AddUObject(this, &UPSGameInstance::OnOpenLevel);
}

void UPSGameInstance::StartGame()
{
	CurrentLifes = PlayerData.Lifes;
}

void UPSGameInstance::OnDeath()
{
	SetPlayerLifes(CurrentLifes - 1);
}

void UPSGameInstance::SetPlayerLifes(const int32 NewLifeAmount)
{
	CurrentLifes = FMath::Clamp(NewLifeAmount, 0, PlayerData.MaxLifes);
}

void UPSGameInstance::PreOpenLevel(const FString& MapName)
{
	SaveWeaponInfo();
}

void UPSGameInstance::OnOpenLevel(UWorld* World)
{
	const auto Controller = PSUtils::GetPlayerController(World);
	if(!Controller) return;

	Controller->PlayerCameraManager->StartCameraFade(1.0f, 0.0f, StartLevelCameraFadeOutDuration, FLinearColor::Black);

	LoadWeaponInfo();
}

void UPSGameInstance::SaveWeaponInfo()
{
	const auto Controller = PSUtils::GetPlayerController(GetWorld());
	if(!Controller) return;

	const auto PlayerCharacter = Controller->GetPawn<APSPlayerCharacter>();
	if(!PlayerCharacter) return;

	Weapons = PlayerCharacter->GetWeaponInfo();
}

void UPSGameInstance::LoadWeaponInfo()
{
	const auto Controller = PSUtils::GetPlayerController(GetWorld());
	if(!Controller) return;

	const auto PlayerCharacter = Controller->GetPawn<APSPlayerCharacter>();
	if(!PlayerCharacter) return;

	PlayerCharacter->LoadWeaponInfo(Weapons);
}
