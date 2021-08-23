// Copyright 2021 Juan Marcelo Portillo. All Rights Reserved.

#pragma once

#include "SlateBasics.h"
#include "SlateExtras.h"
#include "MinesweeperPluginEnums.h"

class SMinesweeperTileWidget : public SCompoundWidget
{
public:

	SLATE_BEGIN_ARGS(SMinesweeperTileWidget) {}
	SLATE_END_ARGS()

public:

	void Construct(const FArguments& InArgs);

	//~ Begin SWidget Interface
	virtual bool SupportsKeyboardFocus() const override { return true; }
	//~ End SWidget Interface

	void UpdateTile();

	FReply OnTileButtonClicked(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent);
	int32 GetActiveWidgetIndex() const;
	const FSlateBrush* GetTileImageBrush() const;

public:

	TSharedPtr<SWidgetSwitcher> WidgetSwitcher;
	TSharedPtr<SImage> TileImage;
	TSharedPtr<STextBlock> NeighborMinesText;

	int32 NeighboringMineCount;
	EMinesweeperTileContent TileContent;
	EMinesweeperTileState TileState;
};
