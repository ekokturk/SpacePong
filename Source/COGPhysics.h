// Copyright (C) 2020, Eser Kokturk. All Rights Reserved.

#pragma once
#include "Component.h"
#include "IPhysicsCollisionEvent.h"

class COGTransform;
class COGBoxShape;
class COGController;
class COGCircleShape;

// COGPhysics - lets move around
class COGPhysics : public Component
{
public:

	static std::vector<COGPhysics*> mPhysicsComponents;

public:

	COGPhysics(GameObject* pGO, bool bGenerateCollisionEvents);
	virtual ~COGPhysics() = default;

	// Return the type of the component
	virtual ComponentType GetType() const override { return ComponentType::Physics; };

	// Check for collision with the other physics component and update normal 
	bool IsColliding(COGPhysics* pOther, exVector2& nNormal);
	
	// Initialize component
	virtual void Initialize() override;

	// Tick physics component
	virtual void Update(float fDeltaT);

	// Destroy component
	virtual void Destroy() override;
	
	void AddCollisionEventListener(IPhysicsCollisionEvent* pEvent);

	// Restrict physics bodies to viewport
	void SetBoundaries();

	// Set velocity magnitude
	void SetSpeed(float fSpeed);

	// Set velocity direction
	void SetDirection(exVector2 nDirection);

	// Get velocity magnitude
	float Speed() const { return mSpeed; };

	// Get Velocity direction
	exVector2 Direction() const { return mDirection;};

	// Set direction from controller
	void OverrideDirection();											

private:

	COGTransform* mTransform;
	COGBoxShape* mBoxShape;
	COGCircleShape* mCircleShape;
	COGController * mController;

	// Velocity magnitude
	float mSpeed;

	// Velocity direction
	exVector2 mDirection;						

	bool mGenerateCollisionEvents;
	std::vector<IPhysicsCollisionEvent*> mCollisionEventListeners;

};


