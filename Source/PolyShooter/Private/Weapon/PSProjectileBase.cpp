// PolyShooter By DChepurkin

#include "Weapon/PSProjectileBase.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

APSProjectileBase::APSProjectileBase()
{
	PrimaryActorTick.bCanEverTick = false;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");
	StaticMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	StaticMeshComponent->SetCollisionResponseToAllChannels(ECR_Ignore);

	ProjectileCollision = CreateDefaultSubobject<USphereComponent>("ProjectileCollision");
	ProjectileCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	ProjectileCollision->SetCollisionResponseToAllChannels(ECR_Overlap);
	ProjectileCollision->SetSphereRadius(10.0f);
	ProjectileCollision->OnComponentBeginOverlap.AddDynamic(this, &APSProjectileBase::OnBeginOverlap);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovement");

	SetRootComponent(StaticMeshComponent);
}

void APSProjectileBase::BeginPlay()
{
	Super::BeginPlay();

	check(StaticMeshComponent);
	check(ProjectileMovement);

	SetLifeSpan(LifeTime);
}

void APSProjectileBase::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                       UPrimitiveComponent* OtherComp,
                                       int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	MakeDamage(OtherActor);
}

void APSProjectileBase::MakeDamage(AActor* DamagedActor)
{
	if(!GetOwner()) return;

	const auto Controller = GetOwner<APawn>()->GetController();
	if(!Controller) return;

	UGameplayStatics::ApplyRadialDamage(GetWorld(), Damage, GetActorLocation(), DamageRadius, nullptr, {GetOwner()},
	                                    GetOwner(), Controller, DoFullDamage);

	Destroy();
}
