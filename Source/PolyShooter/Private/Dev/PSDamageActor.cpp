// PolyShooter By DChepurkin

#include "Dev/PSDamageActor.h"

#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY_STATIC(LogPSDamageActor, All, All)

APSDamageActor::APSDamageActor()
{
	PrimaryActorTick.bCanEverTick = false;
}

void APSDamageActor::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(TimerHandle, this, &APSDamageActor::OnTimer, DamageRate, true);
}

void APSDamageActor::OnTimer()
{
	DrawDebugSphere(GetWorld(), GetActorLocation(), DamageRadius, 24, Color,
	                false, DamageRate, 0.0f, 2.0f);

	UGameplayStatics::ApplyRadialDamage(GetWorld(), Damage, GetActorLocation(), DamageRadius, nullptr,
	                                    {}, this, nullptr, DoFullDamage);
}
