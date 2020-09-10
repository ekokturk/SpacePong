// Copyright (C) 2020, Eser Kokturk. All Rights Reserved.

#pragma once
#include <vector>
#include "GameTypes.h"
#include "Engine/EngineInterface.h"

class GameObject;


/*
 *The world, it contains all of our game objects and defines the order of updates
 */
class World
{
public:

	World(exEngineInterface* pEngine);

	// Create game objects
	void Create(PlayerType eType1, PlayerType eType2);

	// Destroy all objects that are in the world
	void Destroy();

	// Tick all game objects and components
	void Update(float fDeltaT);

	// Initialize world
	void Initialize();
	
	// Render results of the game instance
	void RenderResult();

	// Render player scores
	void RenderScore(PaddleType nPaddleType, int nScore);		

	exEngineInterface * mEngine; 

private:

	// Score to win the match
	int	mWinScore;

	// Winning paddle
	PaddleType mPaddleWon;

	// Objects that are created in the world
	std::vector<GameObject*> mGameObjects;

};

