// Copyright (C) 2020, Eser Kokturk. All Rights Reserved.

#pragma once
#include <vector>
#include <algorithm>
#include "GameTypes.h"

class GameObject;

// Base class for components
class Component
{
public:

	Component(GameObject* pGO): mGO(pGO){ };
	virtual ~Component() = default;

	virtual ComponentType GetType() const = 0;

	virtual void Initialize() { }
	virtual void Destroy() { }

protected:

	template<class T>
	void AddToComponentVector(std::vector<T*>& componentVector)
	{
		componentVector.push_back((T*)this);
	}

	template<class T>
	void RemoveFromComponentVector(std::vector<T*>& componentVector)
	{
		componentVector.erase(std::remove(componentVector.begin(), componentVector.end(), this), componentVector.end());
	}

protected:

	GameObject* mGO;

};
