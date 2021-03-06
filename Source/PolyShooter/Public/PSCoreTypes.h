#pragma once
#include "PSWidgetBase.h"
#include "SPSLoadingScreen.h"

#include "PSCoreTypes.generated.h"

//Weapon

class UBlendSpace1D;
class UAnimSequence;
class UAnimMontage;
class USoundCue;
class APSWeaponBase;

USTRUCT(BlueprintType)
struct FAmmoData
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=Weapon, meta=(ClampMin = "0"))
	int32 Bullets = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=Weapon, DisplayName="Infinite")
	bool IsInfinite = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=Weapon,
		meta=(ClampMin = "0", EditCondition="!IsInfinite"))
	int32 Clips = 0;
};

USTRUCT(BlueprintType)
struct FWeaponAnimData
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=Weapon)
	UBlendSpace1D* IdleWalkBlendSpace = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=Weapon)
	UBlendSpace1D* IdleRunBlendSpace = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=Weapon)
	UAnimMontage* FireAnimMontage = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=Weapon)
	UAnimMontage* ReloadAnimMontage = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=Weapon)
	UAnimMontage* EquipAnimMontage = nullptr;
};

USTRUCT(BlueprintType)
struct FWeaponData
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=Weapon)
	FName AttachSocketName = "WeaponSocket";

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=Weapon)
	FName MuzzleSocketName = "MuzzleSocket";

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=Weapon)
	FName MagazineInSocketName = "MagazineSocket";

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=Weapon)
	FName MagazineOutSocketName = "MagazineSocket";

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=Weapon)
	TSubclassOf<UCameraShakeBase> FireCameraShake;
};

USTRUCT(BlueprintType)
struct FImpactData
{
	GENERATED_BODY()	

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=Weapon)
	UParticleSystem* ImpactVFX = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=Weapon)
	USoundCue* ImpactSoundCue = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=Weapon)
	UMaterial* ImpactMaterial = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=Weapon)
	FName BaseColorName = "BaseColor";

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=Weapon)
	TArray<UTexture2D*> ImpactTextures;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=Weapon)
	FVector ImpactSize{10.0f, 3.0f, 3.0f};

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=Weapon, meta=(ClampMin = "0.1"))
	float ImpactLifeTime = 5.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=Weapon, meta=(ClampMin = "0.1"))
	float ImpactFadeOutTime = 1.0f;
};

USTRUCT(BlueprintType)
struct FWeaponSoundData
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=Weapon)
	USoundCue* AimInSoundCue = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=Weapon)
	USoundCue* FireSoundCue = nullptr;
};

USTRUCT(BlueprintType)
struct FWeaponUIData
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=Weapon)
	UTexture2D* CrossHairImage = nullptr;
};

//Player
USTRUCT(BlueprintType)
struct FPlayerData
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(ClampMin = "1"))
	int32 Lifes = 3;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(ClampMin = "1"))
	int32 MaxLifes = 9;
};

//GameState
UENUM()
enum class EGameState:uint8
{
	InProgress,
	Pause,
	GameOver
};

//UI
USTRUCT(BlueprintType)
struct FWidgetsData
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	EGameState GameState = EGameState::InProgress;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<UPSWidgetBase> WidgetClass;
};
