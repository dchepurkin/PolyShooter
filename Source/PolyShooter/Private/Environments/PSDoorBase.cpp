// PolyShooter By DChepurkin

#include "Environments/PSDoorBase.h"
#include "Components/BoxComponent.h"
#include "Components/TimelineComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

DEFINE_LOG_CATEGORY_STATIC(LogPSDoorBase, All, All);

APSDoorBase::APSDoorBase()
{
	PrimaryActorTick.bCanEverTick = false;

	DoorArchStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("DoorArch");
	SetRootComponent(DoorArchStaticMesh);

	TriggerCollision = CreateDefaultSubobject<UBoxComponent>("TriggerCollision");
	TriggerCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	TriggerCollision->SetCollisionObjectType(ECC_WorldStatic);
	TriggerCollision->SetCollisionResponseToAllChannels(ECR_Ignore);
	TriggerCollision->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	TriggerCollision->SetupAttachment(GetRootComponent());

	OpenDoorTimeline = CreateDefaultSubobject<UTimelineComponent>("OpenDoorTimeline");
}

void APSDoorBase::BeginPlay()
{
	Super::BeginPlay();

	check(TriggerCollision);
	check(DoorArchStaticMesh);

	TriggerCollision->OnComponentBeginOverlap.AddDynamic(this, &APSDoorBase::OnBeginOverlap);
	TriggerCollision->OnComponentEndOverlap.AddDynamic(this, &APSDoorBase::OnEndOverlap);

	UpdateTimelineFloat.BindDynamic(this, &APSDoorBase::OnTimelineTick);
	if(OpenDoorCurve) OpenDoorTimeline->AddInterpFloat(OpenDoorCurve, UpdateTimelineFloat);
}

void APSDoorBase::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
                                 bool bFromSweep, const FHitResult& SweepResult)
{
	GetWorldTimerManager().ClearTimer(CloseDoorTimerHandle);
	Open();
}

void APSDoorBase::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	TArray<AActor*> OverlapedActors;
	TriggerCollision->GetOverlappingActors(OverlapedActors, APawn::StaticClass());
	if(OverlapedActors.IsEmpty()) GetWorldTimerManager().SetTimer(CloseDoorTimerHandle, this, &APSDoorBase::Close, CloseDoorDelay);
}

void APSDoorBase::Open() const
{
	OpenDoorTimeline->Play();
	UGameplayStatics::PlaySoundAtLocation(this, OpenDoorSound, GetActorLocation());
}

void APSDoorBase::Close() const
{
	OpenDoorTimeline->Reverse();
	UGameplayStatics::PlaySoundAtLocation(this, CloseDoorSound, GetActorLocation());
}
