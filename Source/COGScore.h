// Copyright (C) 2020, Eser Kokturk. All Rights Reserved.

#pragma once
#include "Component.h"
#include "GameTypes.h"

class COGScore : public Component
{
public:
	static std::vector<COGScore*> mScoreComponents;

public:
	COGScore(GameObject* pGO, PaddleType nPaddleType);
	virtual ~COGScore() = default;

	// Initialize component
	virtual void Initialize() override;

	// Destroy component
	virtual void Destroy() override;

	// Return component type
	virtual ComponentType GetType() const override { return ComponentType::Score; };

	// Get paddle score
	int Score() const { return mScore; };

	// Get paddle type
	PaddleType GetPaddleType() const { return mPaddleType; };

	
	// Check if paddle scored
	bool CheckForScore(GameObject * pGameObject);		

	// Get paddle that won the game depending on a winning score
	PaddleType GetWinner(int nWinningPoints) const;


private:
	// Current score
	int		   mScore;

	// Type of the paddle depending on the location - Left or Right
	PaddleType mPaddleType;								
	
};



