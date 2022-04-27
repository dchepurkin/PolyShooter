// PolyShooter By DChepurkin

#include "Components/PSHealthComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogPSHealthComponent, All, All)

UPSHealthComponent::UPSHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UPSHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	if(const auto OwnerActor = GetOwner())
	{
		OwnerActor->OnTakeAnyDamage.AddDynamic(this, &UPSHealthComponent::OnTakeAnyDamage);
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

	SetHealth(Health - Damage);	
	if(IsDead()) OnDeath.Broadcast();
}

void UPSHealthComponent::SetHealth(float NewHealth)
{
	Health = FMath::Clamp(NewHealth, 0.0f, MaxHealth);
}
