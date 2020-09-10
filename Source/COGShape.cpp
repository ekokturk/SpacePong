// Copyright (C) 2020, Eser Kokturk. All Rights Reserved.

#include "COGShape.h"

COGShape::COGShape(GameObject* pGO)
	: Component(pGO)
	, mColorMain({ 255, 255, 255, 255 })
	, mColorSecondary({255, 255, 255, 255})
{
}

void COGShape::Initialize()
{
	AddToComponentVector(mShapeComponents);
}

void COGShape::Destroy()
{
	RemoveFromComponentVector(mShapeComponents);
}

// Set main color of the shape
void COGShape::SetColorMain(exColor nColor)
{
	mColorMain = nColor;
}

// Set secondary color of the shape
void COGShape::SetColorSecondary(exColor nColor)
{
	mColorSecondary = nColor;
}


std::vector<COGShape*> COGShape::mShapeComponents;