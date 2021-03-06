// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FToolBarBuilder;
class FMenuBuilder;

class FMinesweeperPluginModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	
	/** This function will be bound to Command. */
	void OpenMinesweeperButtonClicked();

	TSharedRef<class SDockTab> OnSpawnMinesweeperTab(const class FSpawnTabArgs& SpawnTabArgs);

private:

	void RegisterMenus();

private:

	TSharedPtr<class SMinesweeperMainWidget> MinesweeperWindow;
	TSharedPtr<class FUICommandList> PluginCommands;
};
