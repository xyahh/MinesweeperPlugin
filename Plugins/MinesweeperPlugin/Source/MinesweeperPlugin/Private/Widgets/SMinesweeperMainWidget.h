// Copyright 2021 Juan Marcelo Portillo. All Rights Reserved.

#pragma once

#include "SlateBasics.h"
#include "SlateExtras.h"

class SMinesweeperMainWidget : public SCompoundWidget
{
public:

	SLATE_BEGIN_ARGS(SMinesweeperMainWidget) {}
	SLATE_END_ARGS()

public:

	void Construct(const FArguments& InArgs);

	//~ Begin SWidget Interface
	virtual bool SupportsKeyboardFocus() const override { return true; }
	//~ End SWidget Interface

	void OnGameStart(int32 GridWidth, int32 GridHeight, int32 MineCount);

protected:

	TSharedPtr<class SMinesweeperSettingsWidget> SettingsWidget;
	TSharedPtr<class SMinesweeperGameWidget> GameWidget;

};
