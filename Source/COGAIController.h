// Copyright (C) 2020, Eser Kokturk. All Rights Reserved.

#pragma once
#include "COGController.h"

class COGTransform;

class COGAIController : public COGController
{
public:
	COGAIController(GameObject* pGO);
	virtual ~COGAIController() = default;

	// Get direction of the controlled object
	virtual ComponentType GetType() const override { return ComponentType::AIController; };

	// Return direction of the controlled object in screen
	virtual exVector2 GetDirection() override;				

	// Set target that will dictate actions of the AI controller
	void SetTarget(COGTransform* newTarget);
	
private:
	// Target transform
	COGTransform* mTarget;

};


