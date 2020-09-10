// Copyright (C) 2020, Eser Kokturk. All Rights Reserved.

#pragma once
#include <vector>
#include "Component.h"

class exEngineInterface;

// our game object, it's just a collection of components - that's it!
class GameObject
{
public:

	GameObject(exEngineInterface * pEngine);
	~GameObject();

	void Initialize();
	void AddComponent(Component* pComponent);

	template<class T>
	T* FindComponent(ComponentType eType)
	{
		for (Component* pComponent : mComponents)
		{
			if (pComponent->GetType() == eType)
			{
				return (T*)pComponent;
			}
		}
		return nullptr;
	}

	exEngineInterface * mEngine;
private:
	std::vector<Component*> mComponents;

};