// Copyright 2021 Juan Marcelo Portillo. All Rights Reserved.

#include "SMinesweeperSettingsWidget.h"
#include "MinesweeperPluginStyle.h"
#include "Widgets/Layout/SScaleBox.h"

#define LOCTEXT_NAMESPACE "SMinesweeperSettingsWidget"

#define MINESWEEPER_GRIDWIDTH
#define MINESWEEPER_GRIDHEIGHT
#define MINESWEEPER_MINECOUNT
#define MINESWEEPER_STARTGAME

const int32 MinGridSize(2);
const int32 MaxGridSize(100);

const int32 MinMineCount(1);
const int32 MaxMineCount(100);

void SMinesweeperSettingsWidget::Construct(const FArguments& InArgs)
{
	GridWidth = 15;
	GridHeight = 15;
	MineCount = 25;

	//Map the Slate Event delegates to the delegates we are going to use
	OnGameStart = InArgs._OnGameStart;

	const float VerticalPadding = 2.f;

	ChildSlot
	[
		//Scale Settings altogether depending on how small/big the widget is in the screen
		SNew(SScaleBox)
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		.Stretch(EStretch::ScaleToFit)
		[
			SNew(SVerticalBox)

			//Grid Width VerticalBox Slot
#ifdef MINESWEEPER_GRIDWIDTH
			+ SVerticalBox::Slot()
			.Padding(0.f, VerticalPadding)
			.AutoHeight()
			.HAlign(HAlign_Fill)
			[
				SNew(SHorizontalBox)
				
				//Width Settings Name Text Block
				+ SHorizontalBox::Slot()
				.Padding(0.f)
				.FillWidth(1.f)
				.VAlign(EVerticalAlignment::VAlign_Fill)
				[
					SNew(STextBlock)
					.Text(LOCTEXT("SMinesweeperSettingsWidgetGridWidth", "Grid Width: "))
					.Justification(ETextJustify::Right)
					.TextStyle(FMinesweeperPluginStyle::Get(), TEXT("Minesweeper.Text.Settings"))
				]

				//Width Settings Editable Text Box
				+ SHorizontalBox::Slot()
				.Padding(0.f)
				.FillWidth(1.f)
				.VAlign(EVerticalAlignment::VAlign_Fill)
				.MaxWidth(100.f)
				[
					SAssignNew(GridWidthTextBox, SEditableTextBox)
					.Text(FText::AsNumber(GridWidth))
					.Justification(ETextJustify::Left)
					.Font(FMinesweeperPluginStyle::Get().GetFontStyle(TEXT("Minesweeper.Text.Settings")))
					.OnTextCommitted(this, &SMinesweeperSettingsWidget::OnGridWidthTextCommitted)
				]

			]
#endif

			//Grid Height VerticalBox Slot
#ifdef MINESWEEPER_GRIDHEIGHT
			+ SVerticalBox::Slot()
			.Padding(0.f, VerticalPadding)
			.AutoHeight()
			.HAlign(HAlign_Fill)
			[
				SNew(SHorizontalBox)
				
				//Height Settings Name Text Block
				+ SHorizontalBox::Slot()
				.Padding(0.f)
				.FillWidth(1.f)
				.VAlign(EVerticalAlignment::VAlign_Fill)
				[
					SNew(STextBlock)
					.Text(LOCTEXT("SMinesweeperSettingsWidgetGridHeight", "Grid Height: "))
					.Justification(ETextJustify::Right)
					.TextStyle(FMinesweeperPluginStyle::Get(), TEXT("Minesweeper.Text.Settings"))
				]

				//Height Settings Editable Text Box
				+ SHorizontalBox::Slot()
				.Padding(0.f)
				.FillWidth(1.f)
				.VAlign(EVerticalAlignment::VAlign_Fill)
				.MaxWidth(100.f)
				[
					SAssignNew(GridHeightTextBox, SEditableTextBox)
					.Text(FText::AsNumber(GridHeight))
					.Justification(ETextJustify::Left)
					.Font(FMinesweeperPluginStyle::Get().GetFontStyle(TEXT("Minesweeper.Text.Settings")))
					.OnTextCommitted(this, &SMinesweeperSettingsWidget::OnGridHeightTextCommitted)
				]

			]
#endif

			//Mine Count VerticalBox Slot
#ifdef MINESWEEPER_MINECOUNT
			+ SVerticalBox::Slot()
			.Padding(0.f, VerticalPadding)
			.AutoHeight()
			.HAlign(HAlign_Fill)
			[
				SNew(SHorizontalBox)
				
				//Mine Count Settings Name Text Block
				+ SHorizontalBox::Slot()
				.Padding(0.f)
				.FillWidth(1.f)
				.VAlign(EVerticalAlignment::VAlign_Fill)
				[
					SNew(STextBlock)
					.Text(LOCTEXT("SMinesweeperSettingsWidgetMineCount", "Mine Count: "))
					.Justification(ETextJustify::Right)
					.TextStyle(FMinesweeperPluginStyle::Get(), TEXT("Minesweeper.Text.Settings"))
				]

				//Mine Count Settings Editable Text Box
				+ SHorizontalBox::Slot()
				.Padding(0.f)
				.FillWidth(1.f)
				.VAlign(EVerticalAlignment::VAlign_Fill)
				.MaxWidth(100.f)
				[
					SAssignNew(MineCountTextBox, SEditableTextBox)
					.Text(FText::AsNumber(MineCount))
					.Justification(ETextJustify::Left)
					.Font(FMinesweeperPluginStyle::Get().GetFontStyle(TEXT("Minesweeper.Text.Settings")))
					.OnTextCommitted(this, &SMinesweeperSettingsWidget::OnMineCountTextCommitted)
				]

			]
#endif

			//Game Start VerticalBox Slot 
#ifdef MINESWEEPER_STARTGAME
			+ SVerticalBox::Slot()
			.Padding(0.f, VerticalPadding)
			.AutoHeight()
			.HAlign(EHorizontalAlignment::HAlign_Center)
			[
				SNew(SScaleBox)
				.Stretch(EStretch::ScaleToFit)
				[
					SNew(SButton)
					.Text(LOCTEXT("SMinesweeperSettingsWidgetStartGame", "START GAME"))
					.VAlign(EVerticalAlignment::VAlign_Center)
					.HAlign(EHorizontalAlignment::HAlign_Center)
					.TextStyle(FMinesweeperPluginStyle::Get(), TEXT("Minesweeper.Text.StartGame"))
					.DesiredSizeScale(FVector2D(2.f))
					.OnClicked(this, &SMinesweeperSettingsWidget::OnStartGameButtonClicked)
				]
			]
#endif
		]
	];
}

void SMinesweeperSettingsWidget::OnGridWidthTextCommitted(const FText& Text, ETextCommit::Type CommitType)
{
	OnTextCommitted(TEXT("Grid Width"), GridWidth, MinGridSize, MaxGridSize, GridWidthTextBox, CommitType);
}

void SMinesweeperSettingsWidget::OnGridHeightTextCommitted(const FText& Text, ETextCommit::Type CommitType)
{
	OnTextCommitted(TEXT("Grid Height"), GridHeight, MinGridSize, MaxGridSize, GridHeightTextBox, CommitType);
}

void SMinesweeperSettingsWidget::OnMineCountTextCommitted(const FText& Text, ETextCommit::Type CommitType)
{
	OnTextCommitted(TEXT("Mine Count"), MineCount, MinMineCount, MaxMineCount, MineCountTextBox, CommitType);
}

void SMinesweeperSettingsWidget::OnTextCommitted(const FString& SettingsName
	, int32& SettingsVariable
	, int32 SettingsMinValue
	, int32 SettingsMaxValue
	, TSharedPtr<SEditableTextBox>& SettingsTextBox
	, ETextCommit::Type CommitType)
{
	// Check that TextBox is valid and avoid processing OnEnter commits 
	// to avoid redundant calls to this function
	// (pressing Enter takes the widget out of focus resulting in this logic to run more than once)
	if (SettingsTextBox.IsValid() && CommitType != ETextCommit::OnEnter)
	{
		const FString& DesiredValueString = SettingsTextBox->GetText().ToString();
		const int32 DesiredValue = FCString::Atoi(*DesiredValueString);

		//Check that the DesiredValueString was actually numeric and we have a valid DesiredValue integer.
		if (DesiredValueString.IsNumeric())
		{
			//Check that the Value is within the given range
			if(FMath::IsWithinInclusive(DesiredValue, SettingsMinValue, SettingsMaxValue))
			{
				SettingsVariable = DesiredValue;
			} 
			else
			{
				//it's out of range, so display relevant error message.
				DisplayOutOfRangeErrorMessage(SettingsName, SettingsMinValue, SettingsMaxValue);

				//Clamp the value so as to set the variable to the closest value to the user input.
				SettingsVariable = FMath::Clamp(DesiredValue, SettingsMinValue, SettingsMaxValue);
			}
		}
		else
		{
			//if text string was not numeric, display non-numeric error and don't change the value
			DisplayNonNumericErrorMessage(SettingsName);
		}

		//Update the Text box back to the variable because either
		// 1) float might have been input, and we need to chop it
		// 2) a non-numeric text was entered and we need to revert the text box back to old value
		// 3) a number was entered that was out of range, and we are setting it to a value in range closest to the desired value
		SettingsTextBox->SetText(FText::AsNumber(SettingsVariable));
	}
}

void SMinesweeperSettingsWidget::DisplayNonNumericErrorMessage(const FString& SettingsName)
{
	const FText DialogTitle = FText::FromString(TEXT("Non-numeric Input Error"));

	const FText DialogText = FText::Format(
		LOCTEXT("SMinesweeperSettingsWidgetNonNumericErrorMessage"
			, "A non-numeric value was input into {0} settings. Please enter a valid number."),
		FText::FromString(SettingsName)
	);

	FMessageDialog::Open(EAppMsgType::Ok, DialogText, &DialogTitle);
}

void SMinesweeperSettingsWidget::DisplayOutOfRangeErrorMessage(const FString& SettingsName
	, int32 SettingsMinValue
	, int32 SettingsMaxValue)
{
	const FText DialogTitle = FText::FromString(TEXT("Out of Range Input Error"));

	const FText DialogText = FText::Format(
		LOCTEXT("SMinesweeperSettingsWidgetOutOfRangeErrorMessage"
			, "The input value in {0} was out of range. Please enter a valid number between {1} and {2}.")
		, FText::FromString(SettingsName)
		, FText::AsNumber(SettingsMinValue)
		, FText::AsNumber(SettingsMaxValue)
	);

	FMessageDialog::Open(EAppMsgType::Ok, DialogText, &DialogTitle);
}

FReply SMinesweeperSettingsWidget::OnStartGameButtonClicked()
{
	if(MineCount <= GridHeight * GridWidth)
	{
		OnGameStart.ExecuteIfBound(GridWidth, GridHeight, MineCount);
	} 
	else
	{
		const FText DialogTitle = FText::FromString(TEXT("Mine Overflow!"));

		const FText DialogText = FText::Format(
			LOCTEXT("SMinesweeperSettingsWidgetMineOverflowError"
				, "There are more mines ({0}) than available Grid Tiles ({1})!")
			, FText::AsNumber(MineCount)
			, FText::AsNumber(GridWidth * GridHeight)
		);

		FMessageDialog::Open(EAppMsgType::Ok, DialogText, &DialogTitle);
	}
	return FReply::Handled();
}

#undef LOCTEXT_NAMESPACE

