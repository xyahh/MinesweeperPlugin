// Copyright 2021 Juan Marcelo Portillo. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/SlateDelegates.h"

DECLARE_DELEGATE_RetVal_TwoParams(FReply, FOnTileButtonClicked, const FGeometry&, const FPointerEvent&)
DECLARE_DELEGATE_RetVal_ThreeParams(FReply, FOnIndexedTileButtonClicked, const FGeometry&, const FPointerEvent&, int32)
