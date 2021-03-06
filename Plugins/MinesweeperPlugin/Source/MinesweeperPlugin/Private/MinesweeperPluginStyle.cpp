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
	return TEXT("MinesweeperPluginStyle");
}

#define IMAGE_BRUSH( RelativePath, ... ) FSlateImageBrush( Style->RootToContentDir( RelativePath, TEXT(".png") ), __VA_ARGS__ )
#define BOX_BRUSH( RelativePath, ... ) FSlateBoxBrush( Style->RootToContentDir( RelativePath, TEXT(".png") ), __VA_ARGS__ )
#define BORDER_BRUSH( RelativePath, ... ) FSlateBorderBrush( Style->RootToContentDir( RelativePath, TEXT(".png") ), __VA_ARGS__ )
#define TTF_FONT( RelativePath, ... ) FSlateFontInfo( Style->RootToContentDir( RelativePath, TEXT(".ttf") ), __VA_ARGS__ )
#define OTF_FONT( RelativePath, ... ) FSlateFontInfo( Style->RootToContentDir( RelativePath, TEXT(".otf") ), __VA_ARGS__ )

const FVector2D Icon20x20(20.f, 20.f);
const FVector2D Icon40x40(40.f, 40.f);

FVector2D FMinesweeperPluginStyle::GetMinesweeperTileSize()
{
	return Icon40x40;
}

TSharedRef< FSlateStyleSet > FMinesweeperPluginStyle::Create()
{
	TSharedRef< FSlateStyleSet > Style = MakeShareable(new FSlateStyleSet("MinesweeperPluginStyle"));
	Style->SetContentRoot(IPluginManager::Get().FindPlugin("MinesweeperPlugin")->GetBaseDir() / TEXT("Resources"));
	
	//Color Brush Styles
	Style->Set("Minesweeper.WhiteBrush", new FSlateColorBrush(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f)));
	Style->Set("Minesweeper.BlackBrush", new FSlateColorBrush(FLinearColor(0.0f, 0.0f, 0.0f, 1.0f)));

	//Image Brush Styles
	Style->Set("Minesweeper.Icon", new IMAGE_BRUSH(TEXT("Icon40"), Icon40x40));
	Style->Set("Minesweeper.Icon.Small", new IMAGE_BRUSH(TEXT("Icon40"), Icon20x20));

	//Image Brush Styles (for Tiles)
	Style->Set("Minesweeper.Tile.Default", new IMAGE_BRUSH(TEXT(""), GetMinesweeperTileSize(), FLinearColor::Transparent));
	Style->Set("Minesweeper.Tile.Flag", new IMAGE_BRUSH(TEXT("Flag40"), GetMinesweeperTileSize()));
	Style->Set("Minesweeper.Tile.Mine", new IMAGE_BRUSH(TEXT("Icon40"), GetMinesweeperTileSize()));

	const FTextBlockStyle DefaultTextStyle = FCoreStyle::Get().GetWidgetStyle<FTextBlockStyle>("NormalText");

	//Text Styles
	Style->Set("Minesweeper.Text.Title", FTextBlockStyle(DefaultTextStyle)
		.SetFontSize(24)
		.SetColorAndOpacity(FLinearColor::Yellow)
		.SetHighlightColor(FLinearColor::Yellow));

	Style->Set("Minesweeper.Text.Settings", FTextBlockStyle(DefaultTextStyle)
		.SetFontSize(12)
		.SetColorAndOpacity(FLinearColor::White)
		.SetHighlightColor(FLinearColor::White));

	Style->Set("Minesweeper.Text.StartGame", FTextBlockStyle(DefaultTextStyle)
		.SetFontSize(16)
		.SetColorAndOpacity(FLinearColor::Black)
		.SetHighlightColor(FLinearColor::Black));

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
