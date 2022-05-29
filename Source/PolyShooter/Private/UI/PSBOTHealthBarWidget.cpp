// PolyShooter By DChepurkin

#include "UI/PSBOTHealthBarWidget.h"

#include "PSAICharacter.h"
#include "PSHealthComponent.h"
#include "Components/ProgressBar.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY_STATIC(LogBOTHealthBar, All, All);

void UPSBOTHealthBarWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	SetHealthPercent(1.0f);
}

void UPSBOTHealthBarWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	UpdateVisibility();
}

void UPSBOTHealthBarWidget::SetOwnerPawn(APawn* NewOwnerPawn)
{
	OwnerPawn = NewOwnerPawn;

	if(const auto HealthComponent = OwnerPawn->FindComponentByClass<UPSHealthComponent>())
	{
		HealthComponent->OnHealthChanged.AddUObject(this, &UPSBOTHealthBarWidget::SetHealthPercent);
		HealthComponent->OnDeath.AddUObject(this, &UPSBOTHealthBarWidget::OnDeath);
	}
}

void UPSBOTHealthBarWidget::SetHealthPercent(const float HealthPercent)
{
	HealthProgressBar->SetPercent(HealthPercent);

	const auto HealthProgressBarColor = FMath::Lerp(BadColor, GoodColor, HealthPercent);
	HealthProgressBar->SetFillColorAndOpacity(HealthProgressBarColor);
}

void UPSBOTHealthBarWidget::UpdateVisibility()
{
	IsInVisibleDistance() && IsPlayerVisible()
		? SetRenderOpacity(1.0f)
		: SetRenderOpacity(0.0f);
}

bool UPSBOTHealthBarWidget::IsInVisibleDistance()
{
	return GetOwningPlayerPawn() && GetOwningPlayerPawn()->GetDistanceTo(OwnerPawn) <= VisibleDistance;
}

bool UPSBOTHealthBarWidget::IsPlayerVisible()
{
	if(!GetWorld() || !GetOwningPlayerPawn() || !OwnerPawn) return false;

	FHitResult HitResult;
	FCollisionQueryParams CollisionQueryParams;
	TArray<AActor*> IgnoredActors;
	
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APSAICharacter::StaticClass(), IgnoredActors);
	CollisionQueryParams.AddIgnoredActors(IgnoredActors);
	
	GetWorld()->LineTraceSingleByChannel(HitResult, OwnerPawn->GetActorLocation(),
	                                     GetOwningPlayerPawn()->GetActorLocation(), ECC_GameTraceChannel1, CollisionQueryParams);

	return !HitResult.bBlockingHit;
}
