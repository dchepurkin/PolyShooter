// PolyShooter By DChepurkin


#include "Components/PSWeaponFXComponent.h"

#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

UPSWeaponFXComponent::UPSWeaponFXComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UPSWeaponFXComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

void UPSWeaponFXComponent::PlayImpactFX(const FHitResult& HitResult)
{
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), WeaponFXData.ImpactSoundCue, HitResult.ImpactPoint);
}

