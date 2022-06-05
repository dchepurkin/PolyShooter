// PolyShooter By DChepurkin

#include "Environments/PSNextLevel.h"

#include "PSGameModeBase.h"
#include "Components/BoxComponent.h"

APSNextLevel::APSNextLevel()
{
	PrimaryActorTick.bCanEverTick = false;

	NextLevelTrigger = CreateDefaultSubobject<UBoxComponent>("Trigger");
	NextLevelTrigger->SetCollisionResponseToAllChannels(ECR_Ignore);
	NextLevelTrigger->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECR_Overlap);
	SetRootComponent(NextLevelTrigger);
}

void APSNextLevel::BeginPlay()
{
	Super::BeginPlay();

	if(NextLevelTrigger) NextLevelTrigger->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnOverlap);
}

void APSNextLevel::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult)
{
	if(!GetWorld()) return;

	const auto GameMode = GetWorld()->GetAuthGameMode<APSGameModeBase>();
	if(!GameMode) return;

	GameMode->StartNextLevel();
}
