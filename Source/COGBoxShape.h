// Copyright (C) 2020, Eser Kokturk. All Rights Reserved.

#pragma once
#include "COGShape.h"


class COGBoxShape : public COGShape
{
public:

	COGBoxShape(GameObject* pGO, float fWidth, float fHeight);
	virtual ~COGBoxShape() = default;

	// Return type of the component
	virtual ComponentType GetType() const override { return ComponentType::BoxShape; };

	// Get Width
	float Width() const { return mWidth; };

	// Get Height
	float Height() const { return mHeight; };

	// Render component shape
	virtual void Render() override;

private:

	float mWidth;
	float mHeight;

};