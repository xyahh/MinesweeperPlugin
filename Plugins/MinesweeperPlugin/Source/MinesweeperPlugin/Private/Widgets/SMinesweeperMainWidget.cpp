// Copyright 2021 Juan Marcelo Portillo. All Rights Reserved.

#include "SMinesweeperMainWidget.h"
#include "SMinesweeperSettingsWidget.h"
#include "SMinesweeperGameWidget.h"
#include "MinesweeperPluginStyle.h"
#include "Widgets/Layout/SScaleBox.h"

#define LOCTEXT_NAMESPACE "SMinesweeperMainWidget"

void SMinesweeperMainWidget::Construct(const FArguments& InArgs)
{
	const float VerticalPadding(10.f);

	ChildSlot
	[
		SNew(SBorder)
		.BorderBackgroundColor(FLinearColor::Black)
		.Padding(0.f)
		[
			SNew(SVerticalBox)

			//Title
			+ SVerticalBox::Slot()
			.Padding(0.f, VerticalPadding, 0.f, 0.f)
			.VAlign(EVerticalAlignment::VAlign_Fill)
			.FillHeight(0.125f)
			[
				//Scale Title Text depending on how small/big it is on the Screen
				SNew(SScaleBox)
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				.Stretch(EStretch::ScaleToFit)
				[
					SNew(STextBlock)
					.Text(LOCTEXT("MinesweeperMenuTitle", "MINESWEEPER"))
					.Justification(ETextJustify::Center)	
					.TextStyle(FMinesweeperPluginStyle::Get(), FMinesweeperPluginStyle::GetMenuTitleTextStyleName())
				]
			]

			//Minesweeper Settings Widget
			+ SVerticalBox::Slot()
			.Padding(0.f, VerticalPadding, 0.f, 0.f)
			.VAlign(EVerticalAlignment::VAlign_Fill)
			.FillHeight(0.25f)
			[
				SAssignNew(SettingsWidget, SMinesweeperSettingsWidget)
				//Bind OnGameStart to know when the Start button has been pressed and know the Current Settings
				.OnGameStart(this, &SMinesweeperMainWidget::OnGameStart)
			]

			//Minesweeper Game Widget
			+ SVerticalBox::Slot()
			.Padding(0.f, VerticalPadding, 0.f, 0.f)
			.VAlign(EVerticalAlignment::VAlign_Fill)
			.FillHeight(1.f)
			[
				SAssignNew(GameWidget, SMinesweeperGameWidget)
			]
		]
	];
}

void SMinesweeperMainWidget::OnGameStart(int32 GridWidth, int32 GridHeight, int32 MineCount)
{
	if(GameWidget.IsValid())
	{
		//Notify the Game Widget that Game Start has been pressed
		GameWidget->NotifyOnGameStart(GridWidth, GridHeight, MineCount);
	}
}

#undef LOCTEXT_NAMESPACE

