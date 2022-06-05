// PolyShooter By DChepurkin

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PSGameModeBase.generated.h"

UCLASS()
class POLYSHOOTER_API APSGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	void StartFirstLevel();
	void StartNextLevel();
	void ToMenu();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="PSGameMode|Levels")
	FName NextLevelName = "LevelName";

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="PSGameMode|Levels")
	FName FirstLevelName = "Level1";

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="PSGameMode|Levels")
	FName MenuLevelName = "MenuLevel";

private:
	void StartLevel(const FName& LevelName);
	void DisablePlayerCharacter();
};
