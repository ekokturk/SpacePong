// Copyright (C) 2020, Eser Kokturk. All Rights Reserved.

#include "COGTransform.h"

#include <Engine/EngineInterface.h>

COGTransform::COGTransform(GameObject* pGO)
	: Component(pGO), mPosition({0,0})
{
}

bool COGTransform::IsVisible() const
{
	return mPosition.x > 0 && mPosition.x < kViewportWidth&& mPosition.y > 0 && mPosition.x < kViewportHeight;
}

// Set gameobject position
void COGTransform::SetPosition(exVector2 nPosition) { mPosition = nPosition; }