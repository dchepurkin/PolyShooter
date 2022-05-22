// PolyShooter By DChepurkin

#include "UI/PSLoadingScreenWidget.h"

#include "PSHUDBase.h"
#include "Components/Image.h"

void UPSLoadingScreenWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	SetBackgroundImage();
}

void UPSLoadingScreenWidget::SetBackgroundImage()
{
	if(!GetOwningPlayer() || !GetOwningPlayer()->GetHUD<APSHUDBase>()) return;

	const auto BackgroundImages = GetOwningPlayer()->GetHUD<APSHUDBase>()->GetLoadingScreenBackgroundImages();
	const auto ImageIndex = FMath::RandRange(0, BackgroundImages.Num() - 1);
	if(!BackgroundImages[ImageIndex]) return;

	BackgroundImage->SetBrushFromTexture(BackgroundImages[ImageIndex]);
}
