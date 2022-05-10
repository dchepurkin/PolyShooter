// PolyShooter By DChepurkin

#include "Pickup/PSPickupBase.h"

#include "PSHealthComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

DEFINE_LOG_CATEGORY_STATIC(LogPSPickup, All, All);

APSPickupBase::APSPickupBase()
{
	PrimaryActorTick.bCanEverTick = true;

	PickupCollision = CreateDefaultSubobject<USphereComponent>("PickupCollision");
	PickupCollision->SetSphereRadius(50.0f);
	PickupCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	PickupCollision->SetCollisionResponseToAllChannels(ECR_Ignore);
	PickupCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	PickupCollision->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic);
	SetRootComponent(PickupCollision);

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");
	StaticMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	StaticMeshComponent->SetGenerateOverlapEvents(false);
	StaticMeshComponent->SetupAttachment(PickupCollision);
}

void APSPickupBase::BeginPlay()
{
	Super::BeginPlay();

	PickupCollision->OnComponentBeginOverlap.AddDynamic(this, &APSPickupBase::OnBeginOverlap);

	const auto RotationSpeed = FMath::RandRange(MinRotationSpeed, MaxRotationSpeed) * FMath::RandBool() ? 1.0 : -1.0;
	DeltaRotation = FRotator(0.0f, RotationSpeed, 0.0f);
}

void APSPickupBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddActorWorldRotation(DeltaRotation);
}

void APSPickupBase::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                   UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                   const FHitResult& SweepResult)
{
	if(OtherActor && CanTake(OtherActor)) TakePickup(OtherActor);
}

bool APSPickupBase::CanTake(AActor* OtherActor)
{
	const auto HealthComponent = OtherActor->FindComponentByClass<UPSHealthComponent>();
	return HealthComponent && !HealthComponent->IsDead();
}

void APSPickupBase::TakePickup(AActor* OtherActor)
{
	UGameplayStatics::PlaySoundAtLocation(this, TakeSound, GetActorLocation());
	Destroy();
}
