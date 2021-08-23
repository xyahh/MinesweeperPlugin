// Copyright 2021 Juan Marcelo Portillo. All Rights Reserved.

#pragma once

#include "SlateBasics.h"
#include "SlateExtras.h"
#include "MinesweeperPluginStructs.h"
#include "MinesweeperPluginDelegates.h"

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

	void SetTileIndex(int32 InTileIndex) { TileIndex = InTileIndex; }

	FOnIndexedTileButtonClicked& GetOnIndexedTileButtonClickedDelegate() { return OnIndexedTileButtonClicked; }

	void UpdateTile(const FMinesweeperTileInfo& TileInfo);

	FReply OnTileButtonClicked(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent);

protected:

	void UpdateActiveWidget(const FMinesweeperTileInfo& TileInfo);
	void UpdateImageBrush(const FMinesweeperTileInfo& TileInfo);
	void UpdateText(const FMinesweeperTileInfo& TileInfo);

protected:

	TSharedPtr<SWidgetSwitcher> WidgetSwitcher;
	TSharedPtr<SImage> TileImage;
	TSharedPtr<STextBlock> NeighborMinesText;

	int32 TileIndex;

	FOnIndexedTileButtonClicked OnIndexedTileButtonClicked;

};
