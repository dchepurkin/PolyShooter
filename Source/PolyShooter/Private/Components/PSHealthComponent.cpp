// PolyShooter By DChepurkin

#include "Components/PSHealthComponent.h"

#include "GameFramework/Character.h"

DEFINE_LOG_CATEGORY_STATIC(LogPSHealthComponent, All, All)

UPSHealthComponent::UPSHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UPSHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	if(const auto OwnerActor = GetOwner<ACharacter>())
	{
		OwnerActor->OnTakeAnyDamage.AddDynamic(this, &UPSHealthComponent::OnTakeAnyDamage);
		OwnerActor->LandedDelegate.AddDynamic(this, &UPSHealthComponent::OnLanded);
	}

	SetHealth(MaxHealth);
}

void UPSHealthComponent::OnTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
                                         AController* InstigatedBy, AActor* DamageCauser)
{
	ApplyDamage(Damage);
}

void UPSHealthComponent::ApplyDamage(float Damage)
{
	if(Damage <= 0 || IsDead()) return;

	SetAutoHealTimer(false);

	SetHealth(Health - Damage);
	if(Health < MaxHealth) SetAutoHealTimer(true);

	if(IsDead()) { OnDeath.Broadcast(); }
}

void UPSHealthComponent::SetHealth(float NewHealth)
{
	Health = FMath::Clamp(NewHealth, 0.0f, MaxHealth);
}

void UPSHealthComponent::OnLanded(const FHitResult& Hit)
{
	if(!GetOwner()) return;

	const auto LandedVelocity = -GetOwner()->GetVelocity().Z;
	if(LandedVelocity < LandedDamageVelocity.X) return;

	const auto Damage = FMath::GetMappedRangeValueClamped(LandedDamageVelocity, LandedDamage, LandedVelocity);
	ApplyDamage(Damage);
}

void UPSHealthComponent::SetAutoHealTimer(const bool Enabled)
{
	if(!AutoHealEnabled || IsDead() || !GetWorld()) return;

	Enabled
		? GetWorld()->GetTimerManager().SetTimer(AutoHealTimerHandle, this, &UPSHealthComponent::AutoHeal, AutoHealRate,
		                                         true, AutoHealDelay)
		: GetWorld()->GetTimerManager().ClearTimer(AutoHealTimerHandle);
}

void UPSHealthComponent::AutoHeal()
{
	MakeHeal(AutoHealAmount);
	if(FMath::IsNearlyEqual(Health, MaxHealth)) SetAutoHealTimer(false);
}

void UPSHealthComponent::MakeHeal(const float HealthAmount)
{
	if(FMath::IsNearlyZero(HealthAmount)) return;
	SetHealth(Health + HealthAmount);
}
