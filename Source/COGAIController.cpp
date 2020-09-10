// Copyright (C) 2020, Eser Kokturk. All Rights Reserved.

#include "GameObject.h"
#include "COGAIController.h"
#include "COGBoxShape.h"
#include "COGController.h"
#include "COGTransform.h"

COGAIController::COGAIController(GameObject* pGO)
	: ::COGController(pGO), mTarget(nullptr)
{
}

exVector2 COGAIController::GetDirection()
{
	if (mTarget)
	{
		// Get position of the controlled object
		const exVector2 position = mGO->FindComponent<COGTransform>(ComponentType::Transform)->GetPosition();
		// Get height of the controlled object
		const float height = mGO->FindComponent<COGBoxShape>(ComponentType::BoxShape)->Height();					

		// Check if ball is visible in viewport
		if (mTarget->IsVisible())
		{
			// Move paddle when target is in range
			if (fabsf(mTarget->GetPosition().x - position.x) < 500.0f)										
			{
				// Align center of the paddle with target position
				mTarget->GetPosition().y >= position.y + height / 2 ? exVector2{ 0, 1.0f } : exVector2{ 0, -1.0f };
			}
		}
	}
	return { 0, 0 };
}

void COGAIController::SetTarget(COGTransform* newTarget)
{
	mTarget = newTarget;
}

