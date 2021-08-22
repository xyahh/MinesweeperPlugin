// Copyright 2021 Juan Marcelo Portillo. All Rights Reserved.

#include "SMinesweeperGameWidget.h"
#include "MinesweeperPluginStyle.h"

#define LOCTEXT_NAMESPACE "SMinesweeperGameWidget"

void SMinesweeperGameWidget::Construct(const FArguments& InArgs)
{
	ChildSlot
	[
		SNew(SVerticalBox)

		//Horizontal Slot for the Settings
		+ SVerticalBox::Slot()
		.Padding(0.f)
		.AutoHeight()
		[	
			//Title Text Block
			SNew(STextBlock)
			.Text(LOCTEXT("MinesweeperMenuTitle", "MINESWEEPER GAME HERE"))
			.Justification(ETextJustify::Center)
			.TextStyle(FMinesweeperPluginStyle::Get(), FMinesweeperPluginStyle::GetSettingsTextStyleName())
		]
	];
}

void SMinesweeperGameWidget::NotifyOnGameStart(int32 GridWidth, int32 GridHeight, int32 MineCount)
{
	UE_LOG(LogTemp, Warning, TEXT("Game Starting with Grid (%d x %d) and %d mines!")
		, GridWidth
		, GridHeight
		, MineCount);
}

#undef LOCTEXT_NAMESPACE

