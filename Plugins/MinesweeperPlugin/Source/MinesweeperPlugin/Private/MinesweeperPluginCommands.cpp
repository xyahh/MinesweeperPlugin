// Copyright Epic Games, Inc. All Rights Reserved.

#include "MinesweeperPluginCommands.h"

#define LOCTEXT_NAMESPACE "FMinesweeperPluginModule"

void FMinesweeperPluginCommands::RegisterCommands()
{
	UI_COMMAND(OpenMinesweeper, "Minesweeper", "Opens the Minesweeper Minigame in the Editor"
		, EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE
