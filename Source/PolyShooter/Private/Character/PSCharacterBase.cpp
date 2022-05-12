// PolyShooter By DChepurkin

#include "Character/PSCharacterBase.h"

#include "Components/CapsuleComponent.h"
#include "Components/PSHealthComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

APSCharacterBase::APSCharacterBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = false;

	HealthComponent = CreateDefaultSubobject<UPSHealthComponent>("HealthComponent");
}

void APSCharacterBase::BeginPlay()
{
	Super::BeginPlay();

	check(HealthComponent);

	if(HealthComponent)
	{
		HealthComponent->OnDeath.AddUObject(this, &APSCharacterBase::OnDeath);
	}
}

void APSCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void APSCharacterBase::OnDeath()
{
	if(!GetCharacterMovement() || !GetMesh() || !GetCapsuleComponent()) return;

	GetMesh()->SetSimulatePhysics(true);
	GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECR_Ignore);
	GetCharacterMovement()->DisableMovement();
	SetLifeSpan(DeathLifeSpan);
}

