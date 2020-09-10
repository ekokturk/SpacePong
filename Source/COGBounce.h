// Copyright (C) 2020, Eser Kokturk. All Rights Reserved.

#pragma once
#include "GameObject.h"
#include "IPhysicsCollisionEvent.h"


// COGBounce - where we make the ball bounce
class COGBounce : public Component, public IPhysicsCollisionEvent
{
public:

	COGBounce(GameObject* pGO);
	virtual ~COGBounce() = default;

	// Return type of the component
	virtual ComponentType GetType() const override { return ComponentType::Bounce; }

	// Initialize Component
	virtual void Initialize() override;

	// Collision event
	virtual void OnCollision(COGPhysics* pMe, COGPhysics* pOther, exVector2 normal) override;

};