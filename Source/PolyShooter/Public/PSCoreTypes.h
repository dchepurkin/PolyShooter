#pragma once

#include "PSCoreTypes.generated.h"

USTRUCT(BlueprintType)
struct FAmmoData
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=Weapon, meta=(ClampMin = "0"))
	int32 Bullets = 15;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=Weapon, DisplayName="Infinite")
	bool IsInfinite = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=Weapon,
		meta=(ClampMin = "0", EditCondition = "!IsInfinite"))
	int32 Clips = 5;
};
