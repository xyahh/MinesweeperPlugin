// Copyright Epic Games, Inc. All Rights Reserved.

#include "MinesweeperPluginStyle.h"
#include "MinesweeperPlugin.h"
#include "Framework/Application/SlateApplication.h"
#include "Styling/SlateStyleRegistry.h"
#include "Slate/SlateGameResources.h"
#include "Interfaces/IPluginManager.h"

TSharedPtr< FSlateStyleSet > FMinesweeperPluginStyle::StyleInstance = NULL;

void FMinesweeperPluginStyle::Initialize()
{
	if (!StyleInstance.IsValid())
	{
		StyleInstance = Create();
		FSlateStyleRegistry::RegisterSlateStyle(*StyleInstance);
	}
}

void FMinesweeperPluginStyle::Shutdown()
{
	FSlateStyleRegistry::UnRegisterSlateStyle(*StyleInstance);
	ensure(StyleInstance.IsUnique());
	StyleInstance.Reset();
}

FName FMinesweeperPluginStyle::GetStyleSetName()
{
	static FName StyleSetName(TEXT("MinesweeperPluginStyle"));
	return StyleSetName;
}

FSlateIcon FMinesweeperPluginStyle::GetToolbarButtonSlateIcon()
{
	return FSlateIcon(FMinesweeperPluginStyle::GetStyleSetName()
		, FName(TEXT("Minesweeper.Icon")));
}

FSlateIcon FMinesweeperPluginStyle::GetNomadTabSlateIcon()
{
	return FSlateIcon(FMinesweeperPluginStyle::GetStyleSetName()
		, FName(TEXT("Minesweeper.Icon.Small")));
}

#define IMAGE_BRUSH( RelativePath, ... ) FSlateImageBrush( Style->RootToContentDir( RelativePath, TEXT(".png") ), __VA_ARGS__ )
#define BOX_BRUSH( RelativePath, ... ) FSlateBoxBrush( Style->RootToContentDir( RelativePath, TEXT(".png") ), __VA_ARGS__ )
#define BORDER_BRUSH( RelativePath, ... ) FSlateBorderBrush( Style->RootToContentDir( RelativePath, TEXT(".png") ), __VA_ARGS__ )
#define TTF_FONT( RelativePath, ... ) FSlateFontInfo( Style->RootToContentDir( RelativePath, TEXT(".ttf") ), __VA_ARGS__ )
#define OTF_FONT( RelativePath, ... ) FSlateFontInfo( Style->RootToContentDir( RelativePath, TEXT(".otf") ), __VA_ARGS__ )

const FVector2D Icon20x20(20.f, 20.f);
const FVector2D Icon40x40(40.f, 40.f);

TSharedRef< FSlateStyleSet > FMinesweeperPluginStyle::Create()
{
	TSharedRef< FSlateStyleSet > Style = MakeShareable(new FSlateStyleSet("MinesweeperPluginStyle"));
	Style->SetContentRoot(IPluginManager::Get().FindPlugin("MinesweeperPlugin")->GetBaseDir() / TEXT("Resources"));
	
	Style->Set("Minesweeper.Icon", new IMAGE_BRUSH(TEXT("Icon40"), Icon40x40));
	Style->Set("Minesweeper.Icon.Small", new IMAGE_BRUSH(TEXT("Icon40"), Icon20x20));

	return Style;
}

#undef IMAGE_BRUSH
#undef BOX_BRUSH
#undef BORDER_BRUSH
#undef TTF_FONT
#undef OTF_FONT

void FMinesweeperPluginStyle::ReloadTextures()
{
	if (FSlateApplication::IsInitialized())
	{
		FSlateApplication::Get().GetRenderer()->ReloadTextureResources();
	}
}

const ISlateStyle& FMinesweeperPluginStyle::Get()
{
	return *StyleInstance;
}
