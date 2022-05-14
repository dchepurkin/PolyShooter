// PolyShooter By DChepurkin

#include "Components/PSRespawnComponent.h"

#include "PSGameInstance.h"
#include "PSLevelGameModeBase.h"

DEFINE_LOG_CATEGORY_STATIC(LogPSRespawnComponent, All, All);

UPSRespawnComponent::UPSRespawnComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UPSRespawnComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UPSRespawnComponent::StartRespawn()
{
	if(CanRespawn())
	{
		RespawnCountDown = RespawnTime;
		GetWorld()->GetTimerManager().SetTimer(RespawnTimerHandle, this, &UPSRespawnComponent::UpdateRespawnTimer, 1.0f, true);
	}
	else
	{
		GameOver();
	}
}

void UPSRespawnComponent::UpdateRespawnTimer()
{
	if(!--RespawnCountDown && GetWorld())
	{
		GetWorld()->GetTimerManager().ClearTimer(RespawnTimerHandle);
		const auto GameMode = GetWorld()->GetAuthGameMode<APSLevelGameModeBase>();

		if(GameMode) GameMode->RespawnPlayer(GetOwner<AController>());
	}
}

bool UPSRespawnComponent::CanRespawn() const
{
	return GetWorld() &&
		GetWorld()->GetGameInstance<UPSGameInstance>() &&
		GetWorld()->GetGameInstance<UPSGameInstance>()->GetLifes();
}

void UPSRespawnComponent::GameOver()
{
	if(!GetWorld()) return;

	const auto GameMode = GetWorld()->GetAuthGameMode<APSLevelGameModeBase>();
	if(GameMode) GameMode->GameOver();
}
