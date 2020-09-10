// Copyright (C) 2020, Eser Kokturk. All Rights Reserved.

#pragma once
#include "Component.h"
#include "Engine/EngineTypes.h"

class COGController : public Component
{
public:
	static std::vector<COGController*> mControllerComponents;

public:

	// Return direction of the controlled object
	virtual exVector2 GetDirection() = 0;

	// Initialize component
	virtual void Initialize() override;

	// Destroy component
	virtual void Destroy() override;

protected:
	COGController(GameObject* pGO);
	virtual ~COGController() = default;

};

