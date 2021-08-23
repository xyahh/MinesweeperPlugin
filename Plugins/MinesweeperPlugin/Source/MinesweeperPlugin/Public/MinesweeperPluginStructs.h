// Copyright 2021 Juan Marcelo Portillo. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "MinesweeperPluginEnums.h"

struct FMinesweeperTileInfo
{
public:

	FMinesweeperTileInfo()
		: State(EMinesweeperTileState::Default)
		, Content(EMinesweeperTileContent::Nothing)
		, NeighboringMineCount(0)
	{}

public:

	EMinesweeperTileState State;

	EMinesweeperTileContent Content;

	int32 NeighboringMineCount;

	TSharedPtr<class SMinesweeperTileWidget> Widget;
};
