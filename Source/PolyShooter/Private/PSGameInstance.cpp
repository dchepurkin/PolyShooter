// PolyShooter By DChepurkin

#include "PSGameInstance.h"

#include "MoviePlayer.h"
#include "SPSLoadingScreen.h"
#include "PSWeaponBase.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY_STATIC(LogPSGameInstance, All, All);

void UPSGameInstance::Init()
{
	Super::Init();

	//FCoreUObjectDelegates::PreLoadMap.AddUObject(this, &UPSGameInstance::BeginLoadingScreen);
	FCoreUObjectDelegates::PostLoadMapWithWorld.AddUObject(this, &UPSGameInstance::OnOpenLevel);
}

void UPSGameInstance::StartGame()
{
	UE_LOG(LogPSGameInstance,Display,TEXT("Start"))
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

/*inline void UPSGameInstance::BeginLoadingScreen(const FString& MapName)
{
	/*FLoadingScreenAttributes LoadingScreen;
	LoadingScreen.MinimumLoadingScreenDisplayTime = LoadingScreenData.LoadingScreenDelay;
	LoadingScreen.WidgetLoadingScreen = SNew(SPSLoadingScreen, LoadingScreenData.LoadingScreenBackgroundImage);
	LoadingScreen.bAutoCompleteWhenLoadingCompletes = false;

	GetMoviePlayer()->SetupLoadingScreen(LoadingScreen);#1#
}*/

void UPSGameInstance::OnOpenLevel(UWorld* World)
{
	if(!World ||
		!World->GetFirstPlayerController() ||
		!World->GetFirstPlayerController()->PlayerCameraManager)
		return;

	World->GetFirstPlayerController()->PlayerCameraManager->StartCameraFade(1.0f, 0.0f, StartLevelCameraFadeOutDuration, FLinearColor::Black);
}

void UPSGameInstance::SaveAmmoData(const TMap<TSubclassOf<APSWeaponBase>, FAmmoData>& PlayerAmmoData) {}


