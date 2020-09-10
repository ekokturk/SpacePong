// Copyright (C) 2020, Eser Kokturk. All Rights Reserved.

#pragma once
#include "COGShape.h"

// COGCircleShape - box
class COGCircleShape : public COGShape
{
public:

	COGCircleShape(GameObject* pGO, float fRadius);
	virtual ~COGCircleShape() = default;

	// Return type of the component
	virtual ComponentType GetType() const override { return ComponentType::CircleShape; };

	// Return radius of the circle
	float Radius() const { return mRadius; };

	// Render circle shape
	virtual void Render() override;

private:

	float mRadius;

};
