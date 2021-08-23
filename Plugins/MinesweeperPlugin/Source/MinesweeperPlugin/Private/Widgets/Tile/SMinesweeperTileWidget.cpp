// Copyright 2021 Juan Marcelo Portillo. All Rights Reserved.

#include "SMinesweeperTileWidget.h"
#include "SMinesweeperTileButton.h"
#include "MinesweeperPluginStyle.h"
#include "Widgets/Layout/SScaleBox.h"

#define LOCTEXT_NAMESPACE "SMinesweeperTileWidget"

void SMinesweeperTileWidget::Construct(const FArguments& InArgs)
{
	TileState = EMinesweeperTileState::Default;
	const FVector2D TileSize = FMinesweeperPluginStyle::GetMinesweeperTileSize();
	
	//TODO: Test
	NeighboringMineCount = FMath::Rand() % 8; 
	TileContent = (FMath::Rand() % 2 == 1) ? EMinesweeperTileContent::Nothing : EMinesweeperTileContent::Mine;

	ChildSlot
	[
		//Fixed Sized Box to avoid scaling issues when changing the state of the tiles
		SNew(SBox)
		.WidthOverride(TileSize.X)
		.HeightOverride(TileSize.Y)
		[
			SAssignNew(WidgetSwitcher, SWidgetSwitcher)
			
			//Button + Image as Child
			+ SWidgetSwitcher::Slot()
			.HAlign(EHorizontalAlignment::HAlign_Fill)
			.VAlign(EVerticalAlignment::VAlign_Fill)
			[
				SNew(SMinesweeperTileButton)
				.OnTileButtonClicked(this, &SMinesweeperTileWidget::OnTileButtonClicked)
				//Add only Left Mouse Button and Right Mouse Button as these are the only Buttons we will use for click
				.RelevantMouseKeys(TSet<FKey>{EKeys::LeftMouseButton, EKeys::RightMouseButton})
				[
					SAssignNew(TileImage, SImage)
				]
			]

			//Text after Tile has been Broken 
			+ SWidgetSwitcher::Slot()
			.HAlign(EHorizontalAlignment::HAlign_Fill)
			.VAlign(EVerticalAlignment::VAlign_Fill)
			[
				SNew(SScaleBox)
				.Stretch(EStretch::ScaleToFit)
				[
					SAssignNew(NeighborMinesText, STextBlock)
					.Justification(ETextJustify::Center)
				]
			]
		]
	];

	UpdateTile();
}

void SMinesweeperTileWidget::UpdateTile()
{
	//Updates whether we need to show the Button, or the Text
	if (WidgetSwitcher.IsValid())
	{
		WidgetSwitcher->SetActiveWidgetIndex(GetActiveWidgetIndex());
	}

	if (NeighborMinesText.IsValid())
	{
		NeighborMinesText->SetText(FText::AsNumber(NeighboringMineCount));
	}

	if (TileImage.IsValid())
	{
		TileImage->SetImage(GetTileImageBrush());
	}
}

FReply SMinesweeperTileWidget::OnTileButtonClicked(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	if (TileState == EMinesweeperTileState::Default)
	{
		const FKey EffectingButton = MouseEvent.GetEffectingButton();

		if (EffectingButton == EKeys::RightMouseButton)
		{
			TileState = EMinesweeperTileState::Flagged;
			UpdateTile();
			return FReply::Handled();
		}

		if (EffectingButton == EKeys::LeftMouseButton)
		{
			TileState = EMinesweeperTileState::Broken;
			UpdateTile();
			return FReply::Handled();
		}
	}
	return FReply::Unhandled();
}

int32 SMinesweeperTileWidget::GetActiveWidgetIndex() const
{
	if(TileState == EMinesweeperTileState::Broken && TileContent == EMinesweeperTileContent::Nothing)
	{
		return 1; //Index 1 contains the Text Block that shows how many Neighboring mines there are
	}
	return 0; //Index 0 contains the button with an Image representing the Tile (Default, Flag, Mine) when the Tile is not broken
}

const FSlateBrush* SMinesweeperTileWidget::GetTileImageBrush() const
{
	switch(TileState)
	{
	case EMinesweeperTileState::Flagged:
		return FMinesweeperPluginStyle::Get().GetBrush(TEXT("Minesweeper.Tile.Flag"));

	case EMinesweeperTileState::Broken:
		switch(TileContent)
		{
			case EMinesweeperTileContent::Mine:
				return FMinesweeperPluginStyle::Get().GetBrush(TEXT("Minesweeper.Tile.Mine"));
		}
		break;
	}
	return FMinesweeperPluginStyle::Get().GetBrush(TEXT("Minesweeper.Tile.Default"));
}

#undef LOCTEXT_NAMESPACE

