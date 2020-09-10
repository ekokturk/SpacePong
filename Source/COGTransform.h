// Copyright (C) 2020, Eser Kokturk. All Rights Reserved.

#pragma once
#include "Component.h"
#include "Engine/EngineTypes.h"

// COGTransform - where we are in space
class COGTransform : public Component
{
public:

	COGTransform(GameObject* pGO);
	virtual ~COGTransform() = default;

	// Return type of the component
	virtual ComponentType GetType() const override { return ComponentType::Transform; };
	
	exVector2& GetPosition() {  return mPosition; };

	// Return true if component is within the boundaries of viewport
	bool IsVisible() const;

	// Set component position
	void SetPosition(exVector2 nPosition);				

private:
	// Position of the component in the viewport
	exVector2 mPosition;

};