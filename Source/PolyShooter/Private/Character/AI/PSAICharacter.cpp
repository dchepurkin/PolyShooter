// PolyShooter By DChepurkin

#include "Character/AI/PSAICharacter.h"

#include "AIController.h"
#include "BrainComponent.h"
#include "PSBOTHealthBarWidget.h"
#include "PSBOTMovementComponent.h"
#include "PSHealthComponent.h"
#include "PSLevelGameModeBase.h"
#include "PSWeaponComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"

APSAICharacter::APSAICharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UPSBOTMovementComponent>(CharacterMovementComponentName))
{
	PrimaryActorTick.bCanEverTick = false;

	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECR_Ignore);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECR_Block);

	GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
	GetMesh()->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECR_Ignore);

	HealthBar = CreateDefaultSubobject<UWidgetComponent>("HealthBar");
	HealthBar->SetWidgetSpace(EWidgetSpace::Screen);
	HealthBar->SetupAttachment(GetMesh());
	HealthBar->SetDrawAtDesiredSize(true);
}

void APSAICharacter::BeginPlay()
{
	Super::BeginPlay();
	InitHealhBar();
}

void APSAICharacter::OnDeath()
{
	Super::OnDeath();

	WeaponComponent->DestroyComponent(true);

	const auto AIController = GetController<AAIController>();
	if(AIController && AIController->BrainComponent)
	{
		AIController->BrainComponent->Cleanup();
		AIController->Destroy();
	}

	if(GetWorld() && GetWorld()->GetAuthGameMode<APSLevelGameModeBase>())
		GetWorld()->GetAuthGameMode<APSLevelGameModeBase>()->OnBotDead();
}

void APSAICharacter::InitHealhBar()
{
	if(const auto HealthBarWidget = Cast<UPSBOTHealthBarWidget>(HealthBar->GetWidget()))
		HealthBarWidget->SetOwnerPawn(this);
}
