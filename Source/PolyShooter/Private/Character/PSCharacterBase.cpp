// PolyShooter By DChepurkin

#include "Character/PSCharacterBase.h"
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
	if(!GetCharacterMovement()) return;

	GetCharacterMovement()->DisableMovement();
}
