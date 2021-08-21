// Copyright Epic Games, Inc. All Rights Reserved.

#include "MinesweeperPlugin.h"
#include "MinesweeperPluginStyle.h"
#include "MinesweeperPluginCommands.h"
#include "Misc/MessageDialog.h"
#include "ToolMenus.h"
#include "LevelEditor.h"

static const FName MinesweeperPluginTabName("MinesweeperPlugin");

#define LOCTEXT_NAMESPACE "FMinesweeperPluginModule"

void FMinesweeperPluginModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FMinesweeperPluginStyle::Initialize();
	FMinesweeperPluginStyle::ReloadTextures();

	FMinesweeperPluginCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FMinesweeperPluginCommands::Get().OpenMinesweeper,
		FExecuteAction::CreateRaw(this, &FMinesweeperPluginModule::OpenMinesweeperButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FMinesweeperPluginModule::RegisterMenus));
}

void FMinesweeperPluginModule::ShutdownModule()
{
	UToolMenus::UnRegisterStartupCallback(this);
	
	UToolMenus::UnregisterOwner(this);

	FMinesweeperPluginStyle::Shutdown();
	
	FMinesweeperPluginCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(MinesweeperPluginTabName);

}

void FMinesweeperPluginModule::OpenMinesweeperButtonClicked()
{
	FGlobalTabmanager::Get()->TryInvokeTab(MinesweeperPluginTabName);
}

TSharedRef<class SDockTab> FMinesweeperPluginModule::OnSpawnMinesweeperTab(const class FSpawnTabArgs& SpawnTabArgs)
{
	return SNew(SDockTab);
}

void FMinesweeperPluginModule::RegisterMenus()
{
	UToolMenu* const ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar");
	FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("Settings");
	{
		FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FMinesweeperPluginCommands::Get().OpenMinesweeper
			, TAttribute<FText>()
			, TAttribute<FText>()
			, TAttribute<FSlateIcon>(FMinesweeperPluginStyle::GetToolbarButtonSlateIcon())));

		Entry.SetCommandList(PluginCommands);
	}

	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(MinesweeperPluginTabName, FOnSpawnTab::CreateRaw(this, &FMinesweeperPluginModule::OnSpawnMinesweeperTab))
		.SetDisplayName(LOCTEXT("FMinesweeperTabTitle", "Minesweeper"))
		.SetMenuType(ETabSpawnerMenuType::Hidden)
		.SetIcon(FMinesweeperPluginStyle::GetNomadTabSlateIcon());
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FMinesweeperPluginModule, MinesweeperPlugin)