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

	//Gets the Button Icon for the Editor Toolbar
	static FSlateIcon GetToolbarButtonSlateIcon();

	//Gets the Tab Icon for the Minesweeper Tab
	static FSlateIcon GetNomadTabSlateIcon();

private:

	static TSharedRef< class FSlateStyleSet > Create();

private:

	static TSharedPtr< class FSlateStyleSet > StyleInstance;
};