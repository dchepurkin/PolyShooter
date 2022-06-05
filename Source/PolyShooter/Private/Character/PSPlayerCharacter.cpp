// PolyShooter By DChepurkin

#include "Character/PSPlayerCharacter.h"

#include "PSHealthComponent.h"
#include "PSWeaponComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/PSPlayerMovementComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogPSPlayerCharacter, All, All)

APSPlayerCharacter::APSPlayerCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UPSPlayerMovementComponent>(CharacterMovementComponentName))
{
	PrimaryActorTick.bCanEverTick = false;

	GetMesh()->bOwnerNoSee = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("PlayerCamera");
	CameraComponent->SetupAttachment(GetRootComponent());
	CameraComponent->bUsePawnControlRotation = true;

	FirstPersonMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>("FirstPersonMesh");
	FirstPersonMeshComponent->SetupAttachment(CameraComponent);
	FirstPersonMeshComponent->SetCastShadow(false);
	FirstPersonMeshComponent->bOnlyOwnerSee = true;

	GetCapsuleComponent()->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel1);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
}

void APSPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	check(CameraComponent);
	check(FirstPersonMeshComponent);
	check(WeaponComponent);
}

void APSPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if(!PlayerInputComponent) return;

	PlayerInputComponent->BindAxis("MoveForward", this, &APSPlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APSPlayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &APSPlayerCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("TurnAround", this, &APSPlayerCharacter::AddControllerYawInput);

	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &APSPlayerCharacter::StartRun);
	PlayerInputComponent->BindAction("Run", IE_Released, this, &APSPlayerCharacter::StopRun);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &APSPlayerCharacter::StartFire);
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &APSPlayerCharacter::StopFire);
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &APSPlayerCharacter::StopFire);
	PlayerInputComponent->BindAction("Reload", IE_Pressed, WeaponComponent, &UPSWeaponComponent::ChangeClip);

	DECLARE_DELEGATE_OneParam(FOnChangeWeaponSignature, int32);
	PlayerInputComponent->BindAction<FOnChangeWeaponSignature>("Weapon1", IE_Pressed, WeaponComponent, &UPSWeaponComponent::EquipWeapon, 0);
	PlayerInputComponent->BindAction<FOnChangeWeaponSignature>("Weapon2", IE_Pressed, WeaponComponent, &UPSWeaponComponent::EquipWeapon, 1);
	PlayerInputComponent->BindAction<FOnChangeWeaponSignature>("Weapon3", IE_Pressed, WeaponComponent, &UPSWeaponComponent::EquipWeapon, 2);
	PlayerInputComponent->BindAction<FOnChangeWeaponSignature>("Weapon4", IE_Pressed, WeaponComponent, &UPSWeaponComponent::EquipWeapon, 3);
	PlayerInputComponent->BindAction<FOnChangeWeaponSignature>("Weapon5", IE_Pressed, WeaponComponent, &UPSWeaponComponent::EquipWeapon, 4);
	PlayerInputComponent->BindAction<FOnChangeWeaponSignature>("Weapon6", IE_Pressed, WeaponComponent, &UPSWeaponComponent::EquipWeapon, 5);
	PlayerInputComponent->BindAction<FOnChangeWeaponSignature>("Weapon7", IE_Pressed, WeaponComponent, &UPSWeaponComponent::EquipWeapon, 6);
}

void APSPlayerCharacter::MoveForward(float AxisValue)
{
	IsMovingForward = AxisValue > 0.0f;
	AddMovementInput(GetActorForwardVector(), AxisValue);
}

void APSPlayerCharacter::MoveRight(float AxisValue)
{
	AddMovementInput(GetActorRightVector(), AxisValue);
}

void APSPlayerCharacter::StartRun()
{
	if(!HealthComponent || HealthComponent->IsDead()) return;

	WantsToRun = true;
	StopFire();
}

void APSPlayerCharacter::StopRun()
{
	WantsToRun = false;
}

TMap<TSubclassOf<APSWeaponBase>, FAmmoData> APSPlayerCharacter::GetWeaponInfo() const
{
	TMap<TSubclassOf<APSWeaponBase>, FAmmoData> WeaponsInfo;
	if(WeaponComponent) WeaponsInfo = WeaponComponent->GetWeaponInfo();
	
	return WeaponsInfo;
}

void APSPlayerCharacter::LoadWeaponInfo(TMap<TSubclassOf<APSWeaponBase>, FAmmoData>& WeaponsInfo)
{
	if(WeaponComponent) WeaponComponent->LoadWeaponInfo(WeaponsInfo);
}

bool APSPlayerCharacter::IsRunning() const
{
	return WantsToRun && IsMovingForward;
}

void APSPlayerCharacter::StartFire()
{
	if(CanFire()) WeaponComponent->StartFire();
}

void APSPlayerCharacter::StopFire()
{
	if(WeaponComponent) WeaponComponent->StopFire();
}

bool APSPlayerCharacter::CanFire()
{
	return !IsRunning() && GetCharacterMovement() && !GetCharacterMovement()->IsFalling() && WeaponComponent;
}

void APSPlayerCharacter::OnDeath()
{
	Super::OnDeath();
	if(WeaponComponent) WeaponComponent->SpawnAmmoBox();
}
