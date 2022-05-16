// PolyShooter By DChepurkin

#include "UI/PSQuitGameQuestionWidget.h"

#include "PSHUDBase.h"
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
	if(!GetOwningPlayer() || !GetOwningPlayer()->GetHUD<APSHUDBase>()) return;
	
	GetOwningPlayer()->GetHUD<APSHUDBase>()->ShowQuitGameQuiestion(false);
	RemoveFromParent();
}
