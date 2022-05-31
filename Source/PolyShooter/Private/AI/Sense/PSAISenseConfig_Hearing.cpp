// PolyShooter By DChepurkin

#include "AI/Sense/PSAISenseConfig_Hearing.h"

#if WITH_GAMEPLAY_DEBUGGER
#include "GameplayDebuggerCategory.h"
#include "GameplayDebuggerTypes.h"
#endif // WITH_GAMEPLAY_DEBUGGER

#include "Perception/AIPerceptionComponent.h"
#include "Sense/PSAISense_Hearing.h"

DEFINE_LOG_CATEGORY_STATIC(LogPSHearingConfig, All, All);

UPSAISenseConfig_Hearing::UPSAISenseConfig_Hearing(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	DebugColor = FColor::Blue;
	Implementation = UPSAISense_Hearing::StaticClass();
}

TSubclassOf<UAISense> UPSAISenseConfig_Hearing::GetSenseImplementation() const
{
	return Implementation;
}

#if WITH_GAMEPLAY_DEBUGGER
static FString DescribeColorHelper(const FColor& Color)
{
	const int32 MaxColors = GColorList.GetColorsNum();
	for(int32 Idx = 0; Idx < MaxColors; Idx++)
	{
		if(Color == GColorList.GetFColorByIndex(Idx))
		{
			return GColorList.GetColorNameByIndex(Idx);
		}
	}

	return FString(TEXT("color"));
}

void UPSAISenseConfig_Hearing::DescribeSelfToGameplayDebugger(const UAIPerceptionComponent* PerceptionComponent,
                                                              FGameplayDebuggerCategory* DebuggerCategory) const
{
	DebuggerCategory->AddTextLine(FString::Printf(TEXT("%s: {%s}%s"), *GetSenseName(), *GetDebugColor().ToString(), *DescribeColorHelper(GetDebugColor())));

	const AActor* BodyActor = PerceptionComponent->GetBodyActor();
	if(BodyActor != nullptr)
	{
		FVector BodyLocation, BodyFacing;
		PerceptionComponent->GetLocationAndDirection(BodyLocation, BodyFacing);

		DebuggerCategory->AddShape(FGameplayDebuggerShape::MakeCylinder(BodyLocation, HearingRange, 25.0f, GetDebugColor()));
	}
}
#endif // WITH_GAMEPLAY_DEBUGGER
