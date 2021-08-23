// Copyright 2021 Juan Marcelo Portillo. All Rights Reserved.

#include "MinesweeperGameManager.h"
#include "Widgets/Tile/SMinesweeperTileWidget.h"

FMinesweeperGameManager::FMinesweeperGameManager(int32 InGridWidth, int32 InGridHeight, int32 InMineCount, TSharedPtr<SGridPanel>& GridPanel)
	: GridWidth(InGridWidth)
	, GridHeight(InGridHeight)
	, TotalMineCount(InMineCount)
{
	//Clear in case we have an existing grid
	if(GridPanel.IsValid())
	{
		GridPanel->ClearChildren();
	}

	const int32 TotalTiles = InGridWidth * InGridHeight;
	
	BrokenEmptyTiles = 0;

	//Early memory allocation to avoid having to allocate multiple times while adding
	Tiles.Reserve(TotalTiles);

	TArray<int32> TileIndices;
	TileIndices.Reserve(TotalTiles);

	for(int32 y = 0; y < InGridHeight; ++y)
	{
		for (int32 x = 0; x < InGridWidth; ++x)
		{
			FMinesweeperTileInfo& TileInfo = Tiles.Emplace_GetRef();

			const int32 Index = GetIndexFromCoords(x, y);

			TileInfo.State = EMinesweeperTileState::Default;
			TileInfo.Content = EMinesweeperTileContent::Nothing;

			TileInfo.Widget = SNew(SMinesweeperTileWidget);
			TileInfo.Widget->SetTileIndex(Index);
			TileInfo.Widget->UpdateTile(TileInfo);
			TileInfo.Widget->GetOnIndexedTileButtonClickedDelegate().BindRaw(this, &FMinesweeperGameManager::OnTileClicked);

			//Add the Widget to the GridPanel
			GridPanel->AddSlot(x, y)
			[
				TileInfo.Widget.ToSharedRef()
			];

			TileIndices.Emplace(Index);
		}
	}

	//Shuffles the TileIndices to a new random index, so that the first 'n' elements of the array are 
	//the indices where we are going to place the Mines (where n = TotalMineCount)
	for (int32 CurrIndex = 0; CurrIndex < TileIndices.Num(); ++CurrIndex)
	{
		TileIndices.Swap(CurrIndex, FMath::Rand() % TileIndices.Num());
	}

	//Time to place the mines
	for(int32 i = 0; i < TotalMineCount; ++i)
	{
		const int32 TileIndex = TileIndices[i];
		check(Tiles.IsValidIndex(TileIndex));

		Tiles[TileIndex].Content = EMinesweeperTileContent::Mine;

		//update the neighbor count
		IncreaseNeighborsNeighboringMineCount(TileIndex);
	}
}

FMinesweeperGameManager::~FMinesweeperGameManager()
{
	for(FMinesweeperTileInfo& Info : Tiles)
	{
		if(Info.Widget.IsValid())
		{
			Info.Widget->GetOnIndexedTileButtonClickedDelegate().Unbind();
		}
	}
	Tiles.Empty();
}

void FMinesweeperGameManager::IncreaseNeighborsNeighboringMineCount(int32 TileIndex)
{
	int32 TileX, TileY;
	if(GetCoordsFromIndex(TileIndex, TileX, TileY))
	{
		for(int32 DeltaY = -1; DeltaY <= 1; ++DeltaY)
		{
			for(int32 DeltaX = -1; DeltaX <= 1; ++DeltaX)
			{
				//Diagonal Neighbors count so no need for additional checks
				if (FMinesweeperTileInfo* const pTile = GetTile(TileX + DeltaX, TileY + DeltaY))
				{
					++pTile->NeighboringMineCount;
					if(pTile->Widget.IsValid())
						pTile->Widget->UpdateTile(*pTile);
				}
			}
		}
	}
}

void FMinesweeperGameManager::AutoBreakNeighborTiles(int32 X, int32 Y)
{
	for (int32 DeltaY = -1; DeltaY <= 1; ++DeltaY)
	{
		for (int32 DeltaX = -1; DeltaX <= 1; ++DeltaX)
		{
			//Ignore the case where DeltaX and Delta Y are both 0 (i.e. break self)
			if (DeltaX != 0 || DeltaY != 0)
			{
				if(FMinesweeperTileInfo* const BrokenTile = AutoBreakTile(X + DeltaX, Y + DeltaY))
				{
					//Continue breaking if the tile we just broke has no neighboring mines
					if (BrokenTile->NeighboringMineCount == 0)
						AutoBreakNeighborTiles(X + DeltaX, Y + DeltaY);
				}	
			}
		}
	}
}

FMinesweeperTileInfo* FMinesweeperGameManager::AutoBreakTile(int32 X, int32 Y)
{
	if (FMinesweeperTileInfo* const Tile = GetTile(X, Y))
	{
		if (Tile->State == EMinesweeperTileState::Default)
		{
			//Only auto break if we are sure that the Contents are no Mine
			//Auto break cannot make the user lose!
			if (Tile->Content != EMinesweeperTileContent::Mine)
				UpdateTileState(EMinesweeperTileState::Broken, *Tile);
			return Tile;
		}
	}
	return nullptr;
}

FMinesweeperTileInfo* FMinesweeperGameManager::GetTile(int32 X, int32 Y)
{
	if(FMath::IsWithin(X, 0, GridWidth) && FMath::IsWithin(Y, 0, GridHeight))
	{
		const int32 Index = GetIndexFromCoords(X, Y);
		if (Tiles.IsValidIndex(Index))
		{
			return &Tiles[Index];
		}
	}
	return nullptr;
}

int32 FMinesweeperGameManager::GetIndexFromCoords(int32 X, int32 Y) const
{
	return (Y * GridWidth) + X;
}

bool FMinesweeperGameManager::GetCoordsFromIndex(int32 Index, int32& OutX, int32& OutY) const
{
	if(Tiles.IsValidIndex(Index))
	{
		OutX = (Index % GridWidth);
		OutY = (Index / GridWidth);
		return true;
	}
	return false;
}

FReply FMinesweeperGameManager::OnTileClicked(const FGeometry& TileGeometry, const FPointerEvent& MouseEvent, int32 TileIndex)
{
	if(Tiles.IsValidIndex(TileIndex))
	{
		const FKey EffectingButton = MouseEvent.GetEffectingButton();

		if (Tiles[TileIndex].State == EMinesweeperTileState::Default)
		{
			//Set the Default to Flagged if clicking the tile with Right Mouse Button
			if (EffectingButton == EKeys::RightMouseButton)
			{
				UpdateTileState(EMinesweeperTileState::Flagged, Tiles[TileIndex]);
				return FReply::Handled();
			}

			//If Default and Clicking with Left Mouse Button, then Break the Tile and Check what's inside
			if (EffectingButton == EKeys::LeftMouseButton)
			{
				UpdateTileState(EMinesweeperTileState::Broken, Tiles[TileIndex]);
				int32 X, Y;

				//Proceed with breaking Neighbor tiles only if what we are breaking right now isn't a mine
				if(Tiles[TileIndex].Content != EMinesweeperTileContent::Mine 
					&& GetCoordsFromIndex(TileIndex, X, Y)
					&& Tiles[TileIndex].NeighboringMineCount == 0)
				{
					AutoBreakNeighborTiles(X, Y);
				}
				return FReply::Handled();
			}
		} 
		//Toggle Flagged back to Default if we are clicking it with Right Mouse Button
		else if(Tiles[TileIndex].State == EMinesweeperTileState::Flagged && EffectingButton == EKeys::RightMouseButton)
		{
			UpdateTileState(EMinesweeperTileState::Default, Tiles[TileIndex]);
			return FReply::Handled();
		}
	}	
	return FReply::Unhandled();
}

void FMinesweeperGameManager::UpdateTileState(EMinesweeperTileState NewState, FMinesweeperTileInfo& Tile)
{
	if(Tile.State != NewState)
	{
		Tile.State = NewState;

		if (Tile.Widget.IsValid())
			Tile.Widget->UpdateTile(Tile);

		if(NewState == EMinesweeperTileState::Broken)
		{
			switch(Tile.Content)
			{
			case EMinesweeperTileContent::Nothing:
				++BrokenEmptyTiles;
				//Increase Number of Broken Tiles that contain Nothing by 1
				//Win if the remaining number of tiles that are *NOT* BrokenEmptyTile is equal (or less than) than total mines
				if (((GridHeight * GridWidth) - BrokenEmptyTiles) <= TotalMineCount)
				{
					ProcessGameFinish(true);
				}
			break;
			
			//Immediately lose if we broke a mine. Decrease Unbroken Mines by 1
			case EMinesweeperTileContent::Mine:
				ProcessGameFinish(false);
			break;
			}
		}
	}
}

void FMinesweeperGameManager::ProcessGameFinish(bool bGameWon)
{
	OnGameFinished.ExecuteIfBound(bGameWon);
}
