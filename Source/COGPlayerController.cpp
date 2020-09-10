// Copyright (C) 2020, Eser Kokturk. All Rights Reserved.

#include "COGPlayerController.h"

#include <SDL_keyboard.h>

COGPlayerController::COGPlayerController(GameObject* pGO)
	: COGController(pGO),
	mUpKey(SDL_SCANCODE_W),
	mDownKey(SDL_SCANCODE_S)
{

}


// Set paddle direction depending on the user input
exVector2 COGPlayerController::GetDirection()
{
	//	Move paddle up when up key is pressed
	if (SDL_GetKeyboardState(0)[mUpKey])			
	{
		return { 0, -1.0f };
	}
	//	Move paddle down when down key is pressed
	else if (SDL_GetKeyboardState(0)[mDownKey])		
	{
		return { 0, 1.0f };
	}
	// If no key is pressed stop paddle
	else
	{
		return { 0, 0 };
	}								
}

void COGPlayerController::SetKeys(SDL_Scancode upKey, SDL_Scancode downKey)
{
	mUpKey = upKey;		// Assign up key
	mDownKey = downKey;	// Assign down key
}