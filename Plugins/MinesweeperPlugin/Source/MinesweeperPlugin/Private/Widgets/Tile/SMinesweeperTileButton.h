// Copyright 2021 Juan Marcelo Portillo. All Rights Reserved.

#pragma once
#include "Widgets/Input/SButton.h"
#include "MinesweeperPluginDelegates.h"

/*
* Tile Button that overrides the Mouse Behavior from SButton to support all types of Mouse Events \
* and let the delegate handle it more flexibly
*/
class SMinesweeperTileButton : public SButton
{
public:
	
	SLATE_BEGIN_ARGS(SMinesweeperTileButton)
		: _RelevantMouseKeys(TSet<FKey>{EKeys::LeftMouseButton})
		{}

	//Slot for the Button's Content
	SLATE_DEFAULT_SLOT(FArguments, Content)

	// Called when the tile button is clicked
	SLATE_EVENT(FOnTileButtonClicked, OnTileButtonClicked)

	// A Set of Keys to determine if the Mouse Key is relevant to use when processing MouseButtonDown/Up event.
	// needed so we ignore when we need to use another Mouse Key for another use (e.g. Middle Mouse Button for moving/dragging)
	SLATE_ATTRIBUTE(TSet<FKey>, RelevantMouseKeys)

	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

public:

	virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;
	virtual FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;

protected:

	FOnTileButtonClicked OnTileButtonClicked;

	TSet<FKey> RelevantMouseKeys;

};
