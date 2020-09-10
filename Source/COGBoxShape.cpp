// Copyright (C) 2020, Eser Kokturk. All Rights Reserved.

#include "Engine/EngineInterface.h"
#include "COGBoxShape.h"
#include "COGTransform.h"
#include "GameObject.h"

COGBoxShape::COGBoxShape(GameObject* pGO, float fWidth, float fHeight)
	: COGShape(pGO)
	, mWidth(fWidth)
	, mHeight(fHeight)
{
	
}

void COGBoxShape::Render()
{
	exEngineInterface* pEngine = mGO->mEngine;														
	COGTransform* pTransform = mGO->FindComponent<COGTransform>(ComponentType::Transform);			
	const exVector2 position = pTransform->GetPosition();																	
	pEngine->DrawBox(position, { position.x + mWidth, position.y + mHeight }, mColorMain, 0);		
}
