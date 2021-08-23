// Copyright 2021 Juan Marcelo Portillo. All Rights Reserved.

#include "SMinesweeperGameWidget.h"
#include "Tile/SMinesweeperTileWidget.h"
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
			.Offset(TAttribute<FMargin>(this, &SMinesweeperGameWidget::GetGridOffsetMargin))
			[
				SNew(SBorder)
				.BorderBackgroundColor(FLinearColor::White)
				[
					SAssignNew(GridPanel, SGridPanel)
				]
			]
		]
	];
}

void SMinesweeperGameWidget::NotifyOnGameStart(int32 GridWidth, int32 GridHeight, int32 MineCount)
{	
	if(GridPanel.IsValid())
	{
		//Reset the Grid Offset so we always start at the Center
		GridOffset = FVector2D::ZeroVector;
		MinesweeperGameManager = MakeUnique<FMinesweeperGameManager>(GridWidth, GridHeight, MineCount, GridPanel);
		MinesweeperGameManager->GetOnGameFinishedDelegate().BindLambda([](bool bGameWon)
		{
			const FText DialogTitle = FText::FromString(TEXT("Game Finished"));
			if(bGameWon)
			{
				FMessageDialog::Open(EAppMsgType::Ok
					, FText(LOCTEXT("SMinesweeperGameWidgetWinMessage", "Congratulations! You Won!"))
					, &DialogTitle);
			} else
			{
				FMessageDialog::Open(EAppMsgType::Ok
					, FText(LOCTEXT("SMinesweeperGameWidgetWinMessage", "You opened a Mine! You lost!"))
					, &DialogTitle);
			}
		});
	}
}

FReply SMinesweeperGameWidget::OnMouseMove(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	if(MouseEvent.IsMouseButtonDown(EKeys::MiddleMouseButton))
	{
		GridOffset = GetGridOffset() + MouseEvent.GetCursorDelta();
		FReply::Handled();
	}
	return FReply::Unhandled();
}

FVector2D SMinesweeperGameWidget::GetGridOffset() const
{
	const FVector2D HalfGameCanvasSize = GameCanvas->GetCachedGeometry().GetDrawSize() * 0.5f;
	const FVector2D HalfGridSize = GridPanel->GetCachedGeometry().GetDrawSize() * 0.5f;
	const FVector2D TileSize = FMinesweeperPluginStyle::GetMinesweeperTileSize();

	// Clamp the Grid Offset so that we can move a Corner of the Grid to the opposite Game Canvas corner
	// (e.g. the Top Left corner of the Grid to the Bottom Right corner of the Game Canvas), 
	// but always leave at least one Tile inside the Game Canvas (so as to not to lose track of the grid)

	const float OffsetX = FMath::Clamp(GridOffset.X
		, -HalfGameCanvasSize.X - HalfGridSize.X + TileSize.X
		, +HalfGameCanvasSize.X + HalfGridSize.X - TileSize.X);

	const float OffsetY = FMath::Clamp(GridOffset.Y
		, -HalfGameCanvasSize.Y - HalfGridSize.Y + TileSize.Y
		, +HalfGameCanvasSize.Y + HalfGridSize.Y - TileSize.Y);

	return FVector2D(OffsetX, OffsetY);
}

FMargin SMinesweeperGameWidget::GetGridOffsetMargin() const
{
	const FVector2D Offset = GetGridOffset();
	//return Grid Offset, the last two can be Zero since we have AutoSize on
	return FMargin(Offset.X, Offset.Y, 0.f, 0.f);
}

#undef LOCTEXT_NAMESPACE

