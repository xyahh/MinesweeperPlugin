// Copyright 2021 Juan Marcelo Portillo. All Rights Reserved.

#include "SMinesweeperTileButton.h"

#define LOCTEXT_NAMESPACE "SMinesweeperTileButton"

void SMinesweeperTileButton::Construct(const FArguments& InArgs)
{
	OnTileButtonClicked = InArgs._OnTileButtonClicked;
	RelevantMouseKeys = InArgs._RelevantMouseKeys.Get();

	//TODO: If more Arguments are needed, they must also be added and passed here to SButton::Construct as well
	SButton::Construct(SButton::FArguments()
		[
			InArgs._Content.Widget
		]);
}

FReply SMinesweeperTileButton::OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	//The logic here is the same as SButton::OnMouseButtonDown, except
	//instead of hard coding it to LeftMouseButton, we check for the Mouse Keys found in 'RelevantMouseKeys'
	FReply Reply = FReply::Unhandled();

	if (IsEnabled() && (RelevantMouseKeys.Contains(MouseEvent.GetEffectingButton()) || MouseEvent.IsTouchEvent()))
	{
		Press();
		PressedScreenSpacePosition = MouseEvent.GetScreenSpacePosition();

		switch(GetClickMethodFromInputType(MouseEvent))
		{
		case EButtonClickMethod::MouseDown:
			if (OnTileButtonClicked.IsBound())
			{
				Reply = OnTileButtonClicked.Execute(MyGeometry, MouseEvent);
			} else
			{
				Reply = FReply::Handled();
			}
			break;

		case EButtonClickMethod::PreciseClick:
			// do not capture the pointer for precise taps or clicks
			Reply = FReply::Handled();
			break;

		default:
			//we need to capture the mouse for MouseUp events
			Reply = FReply::Handled().CaptureMouse(AsShared());
			break;
		}
	}

	Invalidate(EInvalidateWidget::Layout);

	//return the constructed reply
	return Reply;
}

FReply SMinesweeperTileButton::OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	FReply Reply = FReply::Unhandled();
	const EButtonClickMethod::Type InputClickMethod = GetClickMethodFromInputType(MouseEvent);
	const bool bMustBePressed = InputClickMethod == EButtonClickMethod::DownAndUp || InputClickMethod == EButtonClickMethod::PreciseClick;
	const bool bMeetsPressedRequirements = (!bMustBePressed || (bIsPressed && bMustBePressed));

	if (bMeetsPressedRequirements && ((RelevantMouseKeys.Contains(MouseEvent.GetEffectingButton()) || MouseEvent.IsTouchEvent())))
	{
		Release();

		if (IsEnabled())
		{
			if (InputClickMethod == EButtonClickMethod::MouseDown)
			{
				// NOTE: If we're configured to click on mouse-down/precise-tap, then we never capture the mouse thus
				//       may never receive an OnMouseButtonUp() call.  We make sure that our bIsPressed
				//       state is reset by overriding OnMouseLeave().
			}
			else
			{
				bool bEventOverButton = IsHovered();

				if (!bEventOverButton && MouseEvent.IsTouchEvent())
				{
					bEventOverButton = MyGeometry.IsUnderLocation(MouseEvent.GetScreenSpacePosition());
				}

				if (bEventOverButton)
				{
					// If we asked for a precise tap, all we need is for the user to have not moved their pointer very far.
					const bool bTriggerForTouchEvent = InputClickMethod == EButtonClickMethod::PreciseClick;

					// If we were asked to allow the button to be clicked on mouse up, regardless of whether the user
					// pressed the button down first, then we'll allow the click to proceed without an active capture
					const bool bTriggerForMouseEvent = (InputClickMethod == EButtonClickMethod::MouseUp || HasMouseCapture());

					if (OnTileButtonClicked.IsBound() && (bTriggerForTouchEvent || bTriggerForMouseEvent))
					{
						Reply = OnTileButtonClicked.Execute(MyGeometry, MouseEvent);
					}
				}
			}
		}

		//If the user of the button didn't handle this click, then the button's
		//default behavior handles it.
		if (Reply.IsEventHandled() == false)
		{
			Reply = FReply::Handled();
		}
	}

	//If the user hasn't requested a new mouse captor and the button still has mouse capture,
	//then the default behavior of the button is to release mouse capture.
	if (Reply.GetMouseCaptor().IsValid() == false && HasMouseCapture())
	{
		Reply.ReleaseMouseCapture();
	}

	Invalidate(EInvalidateWidget::Layout);

	return Reply;
}

#undef LOCTEXT_NAMESPACE
