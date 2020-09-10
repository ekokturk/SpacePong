// Copyright (C) 2020, Eser Kokturk. All Rights Reserved.

#include "GameObject.h"

class exEngineInterface;

// Constructor
GameObject::GameObject(exEngineInterface * pEngine)
	: mEngine(pEngine)
{
}

// Destructor
GameObject::~GameObject()
{
	for (Component* pComponent : mComponents)
	{
		pComponent->Destroy();

		delete pComponent;
	}
}

void GameObject::Initialize()
{
	for (Component* pComponent : mComponents)
	{
		pComponent->Initialize();
	}
}

void GameObject::AddComponent(Component* pComponent)
{
	mComponents.push_back(pComponent);
}