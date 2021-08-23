// Copyright 2021 Juan Marcelo Portillo. All Rights Reserved.

#pragma once

#include "SlateBasics.h"
#include "SlateExtras.h"

class SMinesweeperGameWidget : public SCompoundWidget
{
public:

	SLATE_BEGIN_ARGS(SMinesweeperGameWidget) {}
	SLATE_END_ARGS()

public:

	void Construct(const FArguments& InArgs);

	//~ Begin SWidget Interface
	virtual bool SupportsKeyboardFocus() const override { return true; }
	//~ End SWidget Interface

	void NotifyOnGameStart(int32 GridWidth, int32 GridHeight, int32 MineCount);

	virtual FReply OnMouseMove(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent);

	FVector2D GetGridOffset() const;
	FMargin GetGridOffsetMargin() const;

protected:

	TSharedPtr<class SConstraintCanvas> GameCanvas;
	TSharedPtr<SGridPanel> GridPanel;

	FVector2D GridOffset;
};
