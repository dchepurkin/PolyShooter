// PolyShooter By DChepurkin

#include "Weapon/PSProjectileBase.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "PSWeaponFXComponent.h"
#include "Sound/SoundCue.h"

DEFINE_LOG_CATEGORY_STATIC(LogPSProjectile, All, All);

APSProjectileBase::APSProjectileBase()
{
	PrimaryActorTick.bCanEverTick = false;

	ProjectileCollision = CreateDefaultSubobject<USphereComponent>("ProjectileCollision");
	ProjectileCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	ProjectileCollision->SetGenerateOverlapEvents(true);
	ProjectileCollision->SetCollisionResponseToAllChannels(ECR_Block);
	ProjectileCollision->SetSphereRadius(10.0f);
	SetRootComponent(ProjectileCollision);

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");
	StaticMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	StaticMeshComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	StaticMeshComponent->SetupAttachment(ProjectileCollision);

	WeaponFXComponent = CreateDefaultSubobject<UPSWeaponFXComponent>("WeaponFXComponent");

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovement");
	ProjectileMovement->ProjectileGravityScale = 0.0f;
	ProjectileMovement->InitialSpeed = 2000.0f;
	ProjectileMovement->bRotationFollowsVelocity = true;
}

void APSProjectileBase::BeginPlay()
{
	Super::BeginPlay();

	check(StaticMeshComponent);
	check(ProjectileMovement);

	ProjectileCollision->IgnoreActorWhenMoving(GetOwner(), true);
	ProjectileMovement->Velocity = ShotDirection * ProjectileMovement->InitialSpeed;
	ProjectileCollision->OnComponentHit.AddDynamic(this, &APSProjectileBase::OnHit);

	UGameplayStatics::SpawnSoundAttached(FireSoundCue, StaticMeshComponent);
	SetLifeSpan(LifeTime);
}

void APSProjectileBase::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
                              UPrimitiveComponent* OtherComp,
                              FVector NormalImpulse, const FHitResult& Hit)
{
	ProjectileMovement->StopMovementImmediately();
	WeaponFXComponent->PlayImpactFX(Hit);
	MakeDamage();
	Destroy();
}

void APSProjectileBase::MakeDamage()
{
	if(!GetWorld()) return;

	UGameplayStatics::ApplyRadialDamage(GetWorld(), Damage, GetActorLocation(), DamageRadius, nullptr,
	                                    {IgnoreDamageSelf ? GetOwner() : nullptr},
	                                    this, GetController(), DoFullDamage);

	DrawDebugSphere(GetWorld(), GetActorLocation(), DamageRadius, 24, FColor::Red, false, 5.0f, 0, 1.0f);
}

AController* APSProjectileBase::GetController() const
{
	const auto Controller = GetOwner<APawn>()->GetController();
	return Controller ? Controller : nullptr;
}

void APSProjectileBase::SetDirection(const FVector& Direction)
{
	ShotDirection = Direction;
}
