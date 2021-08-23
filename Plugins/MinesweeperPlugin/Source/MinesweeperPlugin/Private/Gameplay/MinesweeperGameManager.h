// Copyright Epic Games, Inc. All Rights Reserved.

#include "CoreMinimal.h"
#include "MinesweeperPluginStructs.h"

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

	FMinesweeperTileInfo* GetTile(int32 X, int32 Y);

	int32 GetIndexFromCoords(int32 X, int32 Y) const;
	bool GetCoordsFromIndex(int32 Index, int32& OutX, int32& OutY) const;

	FReply OnTileClicked(const FGeometry& TileGeometry, const FPointerEvent& MouseEvent, int32 TileIndex);
	void UpdateTileState(EMinesweeperTileState NewState, FMinesweeperTileInfo& Tile);

public:

	TArray<FMinesweeperTileInfo> Tiles;

	int32 GridWidth;
	int32 GridHeight;
	int32 TotalMineCount;
};