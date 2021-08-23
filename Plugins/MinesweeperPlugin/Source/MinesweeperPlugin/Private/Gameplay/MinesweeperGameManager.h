// Copyright Epic Games, Inc. All Rights Reserved.

#include "CoreMinimal.h"
#include "MinesweeperPluginStructs.h"
#include "MinesweeperPluginDelegates.h"

class FMinesweeperGameManager
{

public:

	FMinesweeperGameManager(int32 InGridWidth
		, int32 InGridHeight
		, int32 InMineCount
		, TSharedPtr<class SGridPanel>& GridPanel);

	~FMinesweeperGameManager();

	//For given tile with TileIndex, increases all the neighboring tiles' NeighboringMineCount by 1
	void IncreaseNeighborsNeighboringMineCount(int32 TileIndex);

	//For a Given tile (already broken, or about to be broken), breaks all the unbroken neighbors that have 0 mines nearby (RECURSIVE call!)
	void AutoBreakNeighborTiles(int32 X, int32 Y);

	//Breaks the Tile at given X,Y (must be Default and no mine there since it's automatically called and not called by user's click)
	//returns the Broken tile (nullptr if the break was unsuccessful)
	FMinesweeperTileInfo* AutoBreakTile(int32 X, int32 Y);

	FMinesweeperTileInfo* GetTile(int32 X, int32 Y);

	int32 GetIndexFromCoords(int32 X, int32 Y) const;
	bool GetCoordsFromIndex(int32 Index, int32& OutX, int32& OutY) const;

	FReply OnTileClicked(const FGeometry& TileGeometry, const FPointerEvent& MouseEvent, int32 TileIndex);
	void UpdateTileState(EMinesweeperTileState NewState, FMinesweeperTileInfo& Tile);

	void ProcessGameFinish(bool bGameWon);

	FOnGameFinished& GetOnGameFinishedDelegate() { return OnGameFinished; }

public:

	TArray<FMinesweeperTileInfo> Tiles;

	int32 BrokenEmptyTiles;
	int32 GridWidth;
	int32 GridHeight;
	int32 TotalMineCount;

	FOnGameFinished OnGameFinished;
};