// PolyShooter By DChepurkin

#include "UI/PSQuitGameQuestionWidget.h"

#include "PSHUDLevel.h"
#include "PSLevelGameModeBase.h"
#include "Components/Button.h"

DEFINE_LOG_CATEGORY_STATIC(LogQuestion, All, All);

void UPSQuitGameQuestionWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	YesButton->OnPressed.AddDynamic(this, &UPSQuitGameQuestionWidget::OnYes);
	NoButton->OnPressed.AddDynamic(this, &UPSQuitGameQuestionWidget::OnNo);
}

void UPSQuitGameQuestionWidget::OnYes()
{
	if(!GetWorld()) return;
	if(const auto GameMode = GetWorld()->GetAuthGameMode<APSLevelGameModeBase>())
		GameMode->ToMenu();
}

void UPSQuitGameQuestionWidget::OnNo()
{
	if(!GetOwningPlayer() || !GetOwningPlayer()->GetHUD<APSHUDLevel>()) return;
	
	GetOwningPlayer()->GetHUD<APSHUDLevel>()->ShowQuitGameQuiestion(false);
	RemoveFromParent();
}
