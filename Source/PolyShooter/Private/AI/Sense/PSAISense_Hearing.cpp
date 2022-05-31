// PolyShooter By DChepurkin

#include "AI/Sense/PSAISense_Hearing.h"

#include "AIController.h"
#include "AI/NavigationSystemBase.h"
#include "Perception/AIPerceptionComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogPSHearingSense, All, All);

FPSHearingEvent::FPSHearingEvent()
	: HearingActor(nullptr),
	  NoiseMaker(nullptr),
	  NoiseLocation(FVector::ZeroVector) {}

FPSHearingEvent::FPSHearingEvent(AActor* HearingActor, AActor* NoiseMaker)
	: HearingActor(HearingActor),
	  NoiseMaker(NoiseMaker),
	  NoiseLocation(NoiseMaker->GetActorLocation()) {}

//////////////////////////////////////////////////

UPSAISense_Hearing::FDigestedHearingProperties::FDigestedHearingProperties()
{
	HearingRange = 10.0f;
}

UPSAISense_Hearing::FDigestedHearingProperties::FDigestedHearingProperties(const UPSAISenseConfig_Hearing& Config)
{
	HearingRange = Config.HearingRange;
}

//////////////////////////////////////////////////

UPSAISense_Hearing::UPSAISense_Hearing()
{
	OnNewListenerDelegate.BindUObject(this, &UPSAISense_Hearing::OnNewListenerCallback);
	OnListenerRemovedDelegate.BindUObject(this, &UPSAISense_Hearing::OnListenerRemoveCallback);
}

void UPSAISense_Hearing::RegisterEvent(const FPSHearingEvent& Event)
{
	if(!Event.IsValid()) return;

	RegisteredEvents.Add(Event);
	RequestImmediateUpdate();
}

void UPSAISense_Hearing::ReportHearingEvent(UObject* WorldContextObject, AActor* HearingActor, AActor* NoiseMaker)
{
	if(!WorldContextObject || !HearingActor || !NoiseMaker) return;

	if(const auto PerceptionSystem = UAIPerceptionSystem::GetCurrent(WorldContextObject))
	{
		const FPSHearingEvent Event(HearingActor, NoiseMaker);
		PerceptionSystem->OnEvent(Event);
	}
}

float UPSAISense_Hearing::Update()
{
	if(GetWorld())
	{
		auto& ListenersMap = *GetListeners();
		for(const auto& ListenerMap : ListenersMap)
		{
			auto Listener = ListenerMap.Value;
			const auto ListenerActor = Listener.GetBodyActor();

			for(const auto& Event : RegisteredEvents)
			{
				if(ListenerActor == Event.HearingActor
					|| !IsInHearingDistance(ListenerActor, Event.HearingActor, DesignedProperties[Listener.GetListenerID()].HearingRange)
					|| !IsActorVisible(ListenerActor, Event.HearingActor))
					continue;

				Listener.RegisterStimulus(Event.NoiseMaker, FAIStimulus(*this, 1.f, Event.NoiseMaker->GetActorLocation(),
				                                                        Event.NoiseMaker->GetActorLocation()));
			}
		}
	}

	RegisteredEvents.Reset();

	return FLT_MAX;
}

bool UPSAISense_Hearing::IsInHearingDistance(const AActor* FirstActor, const AActor* SecondActor, const float MaxDistance)
{
	return FirstActor && SecondActor && FirstActor->GetDistanceTo(SecondActor) <= MaxDistance;
}

bool UPSAISense_Hearing::IsActorVisible(const AActor* FirstActor, const AActor* SecondActor)
{
	if(!GetWorld() || !FirstActor || !SecondActor) return false;

	FHitResult HitResult;
	FCollisionQueryParams CollisionQueryParams;
	CollisionQueryParams.AddIgnoredActor(FirstActor);
	GetWorld()->LineTraceSingleByChannel(HitResult, FirstActor->GetActorLocation(), SecondActor->GetActorLocation(), ECC_Visibility, CollisionQueryParams);

	return HitResult.bBlockingHit && HitResult.GetActor() == SecondActor;
}

void UPSAISense_Hearing::OnNewListenerCallback(const FPerceptionListener& PerceptionListener)
{
	if(!PerceptionListener.Listener.Get()) return;

	const auto SenseConfig = PerceptionListener.Listener->GetSenseConfig(GetSenseID());
	const auto HearingSenseConfig = Cast<UPSAISenseConfig_Hearing>(SenseConfig);
	if(!HearingSenseConfig) return;

	const FDigestedHearingProperties DesignedProperty(*HearingSenseConfig);
	DesignedProperties.Add(PerceptionListener.GetListenerID(), DesignedProperty);

	RequestImmediateUpdate();
}

void UPSAISense_Hearing::OnListenerRemoveCallback(const FPerceptionListener& PerceptionListener)
{
	DesignedProperties.Remove(PerceptionListener.GetListenerID());
}
