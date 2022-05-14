// PolyShooter By DChepurkin

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PSGameModeBase.generated.h"

UCLASS()
class POLYSHOOTER_API APSGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=PSGameMode)
	FString NextLevelName = "LevelName";	
};
