// Copyright 2021 Juan Marcelo Portillo. All Rights Reserved.

#include "SMinesweeperGameWidget.h"
#include "MinesweeperPluginStyle.h"
#include "Widgets/Layout/SConstraintCanvas.h"

#define LOCTEXT_NAMESPACE "SMinesweeperGameWidget"

void SMinesweeperGameWidget::Construct(const FArguments& InArgs)
{
	ChildSlot
	[
		SNew(SBorder)
		.BorderImage(FMinesweeperPluginStyle::Get().GetBrush(TEXT("Minesweeper.BlackBrush")))
		.Clipping(EWidgetClipping::ClipToBounds)
		[
			SAssignNew(GameCanvas, SConstraintCanvas)

			+ SConstraintCanvas::Slot()
			.Alignment(FVector2D(0.5f))
			.Anchors(FAnchors(0.5f))
			.AutoSize(true)
			.Offset(TAttribute<FMargin>(this, &SMinesweeperGameWidget::GetGridOffset))
			[
				SAssignNew(GridPanel, SGridPanel)
			]
		]
	];
}

void SMinesweeperGameWidget::NotifyOnGameStart(int32 GridWidth, int32 GridHeight, int32 MineCount)
{	
	if(GridPanel.IsValid())
	{
		GridPanel->ClearChildren();
		//Reset the Grid Offset so we always start at the Center
		GridOffset = FVector2D::ZeroVector;

		for (int32 y = 0; y < GridHeight; ++y)
		{
			for (int32 x = 0; x < GridWidth; ++x)
			{
				GridPanel->AddSlot(x, y)
				[
					SNew(SButton)
				];
			}
		}
	}
}

FReply SMinesweeperGameWidget::OnMouseMove(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	if(MouseEvent.IsMouseButtonDown(EKeys::MiddleMouseButton))
	{
		//Move Grid when Middle Mouse Button is Down
		GridOffset += MouseEvent.GetCursorDelta();
		FReply::Handled();
	}
	return FReply::Unhandled();
}

FMargin SMinesweeperGameWidget::GetGridOffset() const
{
	//return Grid Offset, the last two can be Zero since we have AutoSize on
	return FMargin(GridOffset.X, GridOffset.Y, 0.f, 0.f);
}

#undef LOCTEXT_NAMESPACE

