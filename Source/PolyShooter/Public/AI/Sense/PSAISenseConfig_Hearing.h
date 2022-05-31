// PolyShooter By DChepurkin

#pragma once

#include "CoreMinimal.h"
#include "Perception/AISenseConfig.h"
#include "PSAISenseConfig_Hearing.generated.h"

class UPSAISense_Hearing;
/**
 * 
 */
UCLASS(meta = (DisplayName = "PS AI Hearing config"))
class POLYSHOOTER_API UPSAISenseConfig_Hearing : public UAISenseConfig
{
	GENERATED_BODY()

public:
	UPSAISenseConfig_Hearing(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Sense", NoClear, Config)
	TSubclassOf<UPSAISense_Hearing> Implementation;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Sense", Config, meta=(UIMin = "0.0", ClampMin = "0.0"))
	float HearingRange;

	virtual TSubclassOf<UAISense> GetSenseImplementation() const override;

#if WITH_GAMEPLAY_DEBUGGER
	//в этой функции отрисовывается Debug информация

	virtual void DescribeSelfToGameplayDebugger(const UAIPerceptionComponent* PerceptionComponent, FGameplayDebuggerCategory* DebuggerCategory) const override;
#endif // WITH_GAMEPLAY_DEBUGGER
};
