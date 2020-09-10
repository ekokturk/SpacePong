// Copyright (C) 2020, Eser Kokturk. All Rights Reserved.

#include "Engine/EngineInterface.h"
#include "COGCircleShape.h"
#include "COGTransform.h"
#include "GameObject.h"

COGCircleShape::COGCircleShape(GameObject* pGO, float fRadius)
	: COGShape(pGO)
	, mRadius(fRadius)
{
}

void COGCircleShape::Render()
{
	exEngineInterface* pEngine = mGO->mEngine;													
	COGTransform* pTransform = mGO->FindComponent<COGTransform>(ComponentType::Transform);	
	const exVector2 position = pTransform->GetPosition();											
	pEngine->DrawCircle(position, mRadius, mColorMain, 0);								
}
