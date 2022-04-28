// PolyShooter By DChepurkin

#include "Character/PSPlayerCharacter.h"

#include "PSHealthComponent.h"
#include "PSWeaponComponent.h"
#include "Camera/CameraComponent.h"
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

	WeaponComponent = CreateDefaultSubobject<UPSWeaponComponent>("WeaponComponent");
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

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &APSPlayerCharacter::Jump);
	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &APSPlayerCharacter::OnStartRun);
	PlayerInputComponent->BindAction("Run", IE_Released, this, &APSPlayerCharacter::OnStopRun);
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

void APSPlayerCharacter::OnStartRun()
{
	if(!HealthComponent || HealthComponent->IsDead()) return;
	WantsToRun = true;
}

void APSPlayerCharacter::OnStopRun()
{
	WantsToRun = false;
}

bool APSPlayerCharacter::IsRunning() const
{
	return WantsToRun && IsMovingForward;
}
