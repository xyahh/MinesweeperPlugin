// Copyright 2021 Juan Marcelo Portillo. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Styling/SlateStyle.h"

enum class EMinesweeperTileState
{
	Default,
	Flagged,
	Broken,
};

enum class EMinesweeperTileContent
{
	Nothing,
	Mine,
};