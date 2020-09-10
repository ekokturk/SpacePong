// Copyright (C) 2020, Eser Kokturk. All Rights Reserved.

#include "GameObject.h"
#include "COGScore.h"
#include "COGTransform.h"
#include "COGCircleShape.h"
#include "Engine/EngineInterface.h"


COGScore::COGScore(GameObject* pGO, PaddleType nPaddleType)
	:Component(pGO)
	,mScore(0)
	,mPaddleType(nPaddleType)
{
}


// Check if paddle is scored depending on the ball position
bool COGScore::CheckForScore(GameObject * pGameObject)
{
	// Get ball position
	const exVector2 positionBall = pGameObject->FindComponent<COGTransform>(ComponentType::Transform)->GetPosition();

	if (positionBall.x > kViewportWidth+300)				// If ball went out of the right side boundaries
	{
		if (mPaddleType == PaddleType::PaddleLeft)			// Increase left paddle's score
		{
			mScore++;
			return true;
		}
	}
	else if (positionBall.x < -300)							// If ball went out of the left side boundaries
	{
		if (mPaddleType == PaddleType::PaddleRight)			// Increase right paddle's score
		{
			mScore++;
			return true;
		}
	}
	return false;
}


PaddleType COGScore::GetWinner(int nWinningPoints) const
{
	return mScore >= nWinningPoints ? mPaddleType : PaddleType::None;
}


void COGScore::Initialize()
{
	AddToComponentVector(mScoreComponents);
}

void COGScore::Destroy()
{
	RemoveFromComponentVector(mScoreComponents);
}


std::vector<COGScore*> COGScore::mScoreComponents;
