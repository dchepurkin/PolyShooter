// PolyShooter By DChepurkin

#pragma once

#include "CoreMinimal.h"
#include "Perception/AISense.h"
#include "Sense/PSAISenseConfig_Hearing.h"
#include "PSAISense_Hearing.generated.h"

class IAIPerceptionListenerInterface;

USTRUCT(BlueprintType)
struct FPSHearingEvent
{
	GENERATED_BODY()

	typedef class UPSAISense_Hearing FSenseClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sense")
	AActor* HearingActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sense")
	AActor* NoiseMaker;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sense")
	FVector NoiseLocation;

	FPSHearingEvent();
	FPSHearingEvent(AActor* HearingActor, AActor* NoiseMaker);

	bool IsValid() const { return NoiseMaker != nullptr; }
};

UCLASS(meta = (DisplayName = "PS AI Sense Hearing"))
class POLYSHOOTER_API UPSAISense_Hearing : public UAISense
{
	GENERATED_BODY()

public:
	UPROPERTY()
	TArray<FPSHearingEvent> RegisteredEvents;

	UPSAISense_Hearing();
	void RegisterEvent(const FPSHearingEvent& Event);

	static void ReportHearingEvent(UObject* WorldContextObject, AActor* HearingActor, AActor* NoiseMaker);

protected:
	struct FDigestedHearingProperties
	{
		float HearingRange;

		FDigestedHearingProperties();
		FDigestedHearingProperties(const UPSAISenseConfig_Hearing& Config);
	};

	TMap<FPerceptionListenerID, FDigestedHearingProperties> DesignedProperties;

	virtual float Update() override;

private:
	void OnNewListenerCallback(const FPerceptionListener& PerceptionListener);
	void OnListenerRemoveCallback(const FPerceptionListener& PerceptionListener);

	bool IsInHearingDistance(const AActor* FirstActor, const AActor* SecondActor, const float MaxDistance);
	bool IsActorVisible(const AActor* FirstActor, const AActor* SecondActor);
};
