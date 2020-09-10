// Copyright (C) 2020, Eser Kokturk. All Rights Reserved.

#include "COGController.h"

COGController::COGController(GameObject* pGO) 
	: Component(pGO) 
{

}


void COGController::Initialize()
{
	AddToComponentVector(mControllerComponents);
}

void COGController::Destroy()
{
	RemoveFromComponentVector(mControllerComponents);
}

std::vector<COGController*> COGController::mControllerComponents;
