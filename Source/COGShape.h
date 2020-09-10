// Copyright (C) 2020, Eser Kokturk. All Rights Reserved.

#pragma once
#include "Component.h"
#include "Engine/EngineTypes.h"

class COGShape : public Component
{
public:

	static std::vector<COGShape*> mShapeComponents;

public:

	COGShape(GameObject* pGO);
	virtual void Initialize() override;
	virtual void Destroy() override;
	virtual void Render() = 0;

	// Set primary color of the shape
	void SetColorMain(exColor nColor);

	// Set secondary color of the shape
	void SetColorSecondary(exColor nColor);
	
protected:
	
	// Primary color of the shape
	exColor mColorMain;
	// Secondary color of the shape
	exColor mColorSecondary;


};


