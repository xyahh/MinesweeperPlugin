// Copyright Epic Games, Inc. All Rights Reserved.

#include "MinesweeperPlugin.h"
#include "MinesweeperPluginStyle.h"
#include "MinesweeperPluginCommands.h"
#include "Misc/MessageDialog.h"
#include "ToolMenus.h"

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
		FMinesweeperPluginCommands::Get().PluginAction,
		FExecuteAction::CreateRaw(this, &FMinesweeperPluginModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FMinesweeperPluginModule::RegisterMenus));
}

void FMinesweeperPluginModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FMinesweeperPluginStyle::Shutdown();

	FMinesweeperPluginCommands::Unregister();
}

void FMinesweeperPluginModule::PluginButtonClicked()
{
	// Put your "OnButtonClicked" stuff here
	FText DialogText = FText::Format(
							LOCTEXT("PluginButtonDialogText", "Add code to {0} in {1} to override this button's actions"),
							FText::FromString(TEXT("FMinesweeperPluginModule::PluginButtonClicked()")),
							FText::FromString(TEXT("MinesweeperPlugin.cpp"))
					   );
	FMessageDialog::Open(EAppMsgType::Ok, DialogText);
}

void FMinesweeperPluginModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FMinesweeperPluginCommands::Get().PluginAction, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("Settings");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FMinesweeperPluginCommands::Get().PluginAction));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FMinesweeperPluginModule, MinesweeperPlugin)