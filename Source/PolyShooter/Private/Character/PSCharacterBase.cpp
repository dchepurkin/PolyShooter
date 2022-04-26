// PolyShooter By DChepurkin

#include "Character/PSCharacterBase.h"

APSCharacterBase::APSCharacterBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = false;
}

void APSCharacterBase::BeginPlay()
{
	Super::BeginPlay();
}

void APSCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
