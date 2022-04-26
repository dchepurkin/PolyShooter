// PolyShooter By DChepurkin

#include "Character/PSPlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/PSPlayerMovementComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogPSPlayerCharacter, All, All)

APSPlayerCharacter::APSPlayerCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UPSPlayerMovementComponent>(CharacterMovementComponentName))
{
	PrimaryActorTick.bCanEverTick = false;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(GetRootComponent());

	GetMesh()->SetCastShadow(false);
}

void APSPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	check(CameraComponent);
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
}

void APSPlayerCharacter::MoveForward(float AxisValue)
{
	const auto MovementComponent = FindComponentByClass<UPSPlayerMovementComponent>();
	if(!MovementComponent) return;

	MovementComponent->MoveForward(AxisValue);
}

void APSPlayerCharacter::MoveRight(float AxisValue)
{
	const auto MovementComponent = FindComponentByClass<UPSPlayerMovementComponent>();
	if(!MovementComponent) return;

	MovementComponent->MoveRight(AxisValue);
}
