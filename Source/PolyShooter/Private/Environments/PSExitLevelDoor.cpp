// PolyShooter By DChepurkin

#include "Environments/PSExitLevelDoor.h"

#include "PSLevelGameModeBase.h"
DEFINE_LOG_CATEGORY_STATIC(LogDor, All, All);

void APSExitLevelDoor::Open() const
{
	if(CanExitLevel()) Super::Open();
}

bool APSExitLevelDoor::CanExitLevel() const
{
	if(!GetWorld()) return false;

	return GetWorld()->GetAuthGameMode<APSLevelGameModeBase>() &&
		GetWorld()->GetAuthGameMode<APSLevelGameModeBase>()->CanExitLevel();
}
