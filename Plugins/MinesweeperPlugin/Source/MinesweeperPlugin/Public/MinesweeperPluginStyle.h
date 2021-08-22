// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Styling/SlateStyle.h"

class FMinesweeperPluginStyle
{
public:

	static void Initialize();

	static void Shutdown();

	/** reloads textures used by slate renderer */
	static void ReloadTextures();

	/** @return The Slate style set for the Shooter game */
	static const ISlateStyle& Get();

	static FName GetStyleSetName();

	//Gets the set name for the Default sized (40x) Minesweeper Icon (used for the Editor Toolbar)
	static FName GetMinesweeperIconName();

	//Gets the set name for the Small sized (20x) Minesweeper Icon (used for the icon in the Minesweeper Tab)
	static FName GetMinesweeperIconSmallName();

	//Gets the set name for the Title Style
	static FName GetMenuTitleTextStyleName();

	//Gets the set name for the Text Styles of Settings
	static FName GetSettingsTextStyleName();

	//Gets the set name for the Text Styles of Start Game (Button Text)
	static FName GetStartGameTextStyleName();

private:

	static TSharedRef< class FSlateStyleSet > Create();

private:

	static TSharedPtr< class FSlateStyleSet > StyleInstance;
};