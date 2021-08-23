// Copyright 2021 Juan Marcelo Portillo. All Rights Reserved.

#include "SMinesweeperTileWidget.h"
#include "SMinesweeperTileButton.h"
#include "MinesweeperPluginStyle.h"
#include "Widgets/Layout/SScaleBox.h"

#define LOCTEXT_NAMESPACE "SMinesweeperTileWidget"

void SMinesweeperTileWidget::Construct(const FArguments& InArgs)
{
	const FVector2D TileSize = FMinesweeperPluginStyle::GetMinesweeperTileSize();
	
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
}

void SMinesweeperTileWidget::UpdateTile(const FMinesweeperTileInfo& TileInfo)
{
	UpdateActiveWidget(TileInfo);
	UpdateImageBrush(TileInfo);
	UpdateText(TileInfo);
}

FReply SMinesweeperTileWidget::OnTileButtonClicked(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{	
	if(OnIndexedTileButtonClicked.IsBound())
	{
		OnIndexedTileButtonClicked.Execute(MyGeometry, MouseEvent, TileIndex);
	}
	return FReply::Handled();
}

void SMinesweeperTileWidget::UpdateActiveWidget(const FMinesweeperTileInfo& TileInfo)
{
	//Updates whether we need to show the Button, or the Text
	if (WidgetSwitcher.IsValid())
	{
		//Only show the Neighboring mines if we break the Tile and there was nothing
		if (TileInfo.State == EMinesweeperTileState::Broken
			&& TileInfo.Content == EMinesweeperTileContent::Nothing)
		{
			//Index 1 contains the Text Block that shows how many Neighboring mines there are
			WidgetSwitcher->SetActiveWidgetIndex(1);
		}
		else
		{
			//Index 0 contains the button with an Image representing the Tile (Default, Flag, Mine) when the Tile is not broken
			WidgetSwitcher->SetActiveWidgetIndex(0);
		}
	}
}

void SMinesweeperTileWidget::UpdateImageBrush(const FMinesweeperTileInfo& TileInfo)
{
	if (TileImage.IsValid())
	{
		const auto GetTileImageBrush = [](const FMinesweeperTileInfo& TileInfo) -> const FSlateBrush*
		{
			switch (TileInfo.State)
			{
			case EMinesweeperTileState::Flagged:
				return FMinesweeperPluginStyle::Get().GetBrush(TEXT("Minesweeper.Tile.Flag"));

			case EMinesweeperTileState::Broken:
				switch (TileInfo.Content)
				{
				case EMinesweeperTileContent::Mine:
					return FMinesweeperPluginStyle::Get().GetBrush(TEXT("Minesweeper.Tile.Mine"));
				}
				break;
			}
			return FMinesweeperPluginStyle::Get().GetBrush(TEXT("Minesweeper.Tile.Default"));
		};

		TileImage->SetImage(GetTileImageBrush(TileInfo));
	}
}

void SMinesweeperTileWidget::UpdateText(const FMinesweeperTileInfo& TileInfo)
{
	if (NeighborMinesText.IsValid())
	{
		if (TileInfo.NeighboringMineCount > 0)
			NeighborMinesText->SetText(FText::AsNumber(TileInfo.NeighboringMineCount));
		else
			NeighborMinesText->SetText(FText()); //Don't show any text if there are no neighboring mines
	}
}



#undef LOCTEXT_NAMESPACE

