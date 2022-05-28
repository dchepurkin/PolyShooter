// PolyShooter By DChepurkin

#include "Components/PSWeaponFXComponent.h"

#include "Components/DecalComponent.h"
#include "Kismet/GameplayStatics.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "Sound/SoundCue.h"

DEFINE_LOG_CATEGORY_STATIC(LogWeaponFXComponent, All, All)

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
	auto CurrentImpactData = DefaultImpactData;
	if(HitResult.PhysMaterial.IsValid() && ImpactData.Contains(HitResult.PhysMaterial.Get()))
	{
		CurrentImpactData = ImpactData[HitResult.PhysMaterial.Get()];
	}

	UGameplayStatics::PlaySoundAtLocation(GetWorld(), CurrentImpactData.ImpactSoundCue, HitResult.ImpactPoint, HitResult.ImpactNormal.Rotation());
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), CurrentImpactData.ImpactVFX, HitResult.ImpactPoint, HitResult.ImpactNormal.Rotation());

	SpawnDecal(HitResult, CurrentImpactData);
}

void UPSWeaponFXComponent::SpawnDecal(const FHitResult& HitResult, FImpactData& CurrentImpactData)
{
	const auto ImpactMaterial = UMaterialInstanceDynamic::Create(CurrentImpactData.ImpactMaterial, this);
	if(!ImpactMaterial) return;

	const int32 ImpactTextureIndex = FMath::RandRange(0, CurrentImpactData.ImpactTextures.Num() - 1);
	if(!CurrentImpactData.ImpactTextures.Num()) return;

	ImpactMaterial->SetTextureParameterValue(CurrentImpactData.BaseColorName, CurrentImpactData.ImpactTextures[ImpactTextureIndex]);

	const auto Decal = UGameplayStatics::SpawnDecalAtLocation(GetWorld(), ImpactMaterial, CurrentImpactData.ImpactSize, HitResult.ImpactPoint,
	                                                          HitResult.ImpactNormal.Rotation());
	if(!Decal) return;

	Decal->SetFadeScreenSize(0.0f);
	Decal->SetFadeOut(CurrentImpactData.ImpactLifeTime, CurrentImpactData.ImpactFadeOutTime);
}
