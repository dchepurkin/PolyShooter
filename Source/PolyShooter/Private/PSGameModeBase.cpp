// PolyShooter By DChepurkin

#include "PSGameModeBase.h"

#include "PSGameInstance.h"
#include "PSHUDBase.h"
#include "PSUtils.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY_STATIC(LogPSGameMode, All, All);

void APSGameModeBase::StartFirstLevel()
{
	if(const auto GameInstance = GetGameInstance<UPSGameInstance>()) GameInstance->StartGame();
	StartLevel(FirstLevelName);
}

void APSGameModeBase::StartNextLevel()
{
	DisablePlayerCharacter();

	StartLevel(NextLevelName);
}

void APSGameModeBase::DisablePlayerCharacter()
{
	const auto Controller = PSUtils::GetPlayerController(GetWorld());
	if(!Controller) return;

	const auto Pawn = Controller->GetPawn();
	if(!Pawn) return;
	
	Pawn->TurnOff();
	Pawn->DisableInput(nullptr);
}

void APSGameModeBase::ToMenu()
{
	StartLevel(MenuLevelName);
}

void APSGameModeBase::StartLevel(const FName& LevelName)
{
	const auto Controller = PSUtils::GetPlayerController(GetWorld());
	if(!Controller) return;

	const auto HUD = Controller->GetHUD<APSHUDBase>();
	if(!HUD) return;

	HUD->ShowLoadingScreen();
	HUD->OnLoadingScreenFinished.AddWeakLambda(this, [this, &LevelName]() { UGameplayStatics::OpenLevel(GetWorld(), LevelName); });
}
