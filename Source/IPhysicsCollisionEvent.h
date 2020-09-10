// Copyright (C) 2020, Eser Kokturk. All Rights Reserved.

#pragma once
#include "Engine/EngineTypes.h"

class COGPhysics;

// our interface that allows COGPhysics to talk to anyone

class IPhysicsCollisionEvent
{
public:

	virtual void OnCollision(COGPhysics* pMe, COGPhysics* pOther, exVector2 normal) = 0;

};
