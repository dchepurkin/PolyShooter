#pragma once

#include "SlateOptMacros.h"
#include "Slate/DeferredCleanupSlateBrush.h"
#include "Widgets/SCanvas.h"
#include "Widgets/SCompoundWidget.h"
#include "Widgets/Images/SImage.h"


BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

#define LOCTEXT_NAMESPACE "SPSLoadingScreen"

class SPSLoadingScreen : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SPSLoadingScreen) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, UTexture2D* Background)
	{
		if(Background)
		{			
			const auto ImageBrush = FDeferredCleanupSlateBrush::CreateBrush(Background);
			ChildSlot
			   .VAlign(VAlign_Fill)
			   .HAlign(HAlign_Fill)
				[
					SNew(SImage)
				   .Image(ImageBrush->GetSlateBrush())
				];
		}
	}
};

#undef LOCTEXT_NAMESPACE

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
