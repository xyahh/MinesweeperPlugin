// Copyright 2021 Juan Marcelo Portillo. All Rights Reserved.

#pragma once

#include "SlateBasics.h"
#include "SlateExtras.h"


DECLARE_DELEGATE_ThreeParams(FOnGameStart, int32, int32, int32);

class SMinesweeperSettingsWidget : public SCompoundWidget
{
public:

	SLATE_BEGIN_ARGS(SMinesweeperSettingsWidget) {}

	//Called when the Start Button is Pressed
	SLATE_EVENT(FOnGameStart, OnGameStart)

	SLATE_END_ARGS()

public:

	void Construct(const FArguments& InArgs);

	//~ Begin SWidget Interface
	virtual bool SupportsKeyboardFocus() const override { return true; }
	//~ End SWidget Interface

	//Called when Text has been Committed to the Grid Width Editable Text Box
	void OnGridWidthTextCommitted(const FText& Text, ETextCommit::Type CommitType);

	//Called when Text has been Committed to the Grid Height Editable Text Box
	void OnGridHeightTextCommitted(const FText& Text, ETextCommit::Type CommitType);

	//Called when Text has been Committed to the Mine Count Editable Text Box
	void OnMineCountTextCommitted(const FText& Text, ETextCommit::Type CommitType);

	void OnTextCommitted(const FString& SettingsName
		, int32& SettingsVariable
		, int32 SettingsMinValue 
		, int32 SettingsMaxValue
		, TSharedPtr<SEditableTextBox>& SettingsTextBox
		, ETextCommit::Type CommitType);

	void DisplayNonNumericErrorMessage(const FString& SettingsName);
	void DisplayOutOfRangeErrorMessage(const FString& SettingsName
		, int32 SettingsMinValue
		, int32 SettingsMaxValue);

	FReply OnStartGameButtonClicked();

protected:

	int32 GridWidth;
	int32 GridHeight;
	int32 MineCount;

	//Delegate that is called when the Start Button is Pressed
	FOnGameStart OnGameStart;

	TSharedPtr<SEditableTextBox> GridWidthTextBox;
	TSharedPtr<SEditableTextBox> GridHeightTextBox;
	TSharedPtr<SEditableTextBox> MineCountTextBox;
};
