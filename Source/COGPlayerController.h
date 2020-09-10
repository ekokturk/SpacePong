// Copyright (C) 2020, Eser Kokturk. All Rights Reserved.

#pragma once
#include <SDL_scancode.h>
#include "COGController.h"



class COGPlayerController : public COGController
{
public:
	COGPlayerController(GameObject* pGO);
	~COGPlayerController() = default;

	// Return component type
	virtual ComponentType GetType() const override { return ComponentType::PlayerController; };
	virtual exVector2 GetDirection() override;
	
	void SetKeys(SDL_Scancode upKey, SDL_Scancode downKey);
	
private:

	// Key to move up
	SDL_Scancode mUpKey;

	// Key to move down
	SDL_Scancode mDownKey;		
};

