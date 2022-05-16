// PolyShooter By DChepurkin

#include "PSGameModeBase.h"

#include "PSGameInstance.h"
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
	StartLevel(NextLevelName);
}

void APSGameModeBase::ToMenu()
{
	StartLevel(MenuLevelName);
}

void APSGameModeBase::StartLevel(const FName& LevelName)
{
	UGameplayStatics::OpenLevel(GetWorld(), LevelName);
}
