// Copyright (C) 2020, Eser Kokturk. All Rights Reserved.

#include <random>
#include "GameObject.h"
#include "COGPhysics.h"

#include "COGBoxShape.h"
#include "COGCircleShape.h"
#include "COGController.h"
#include "COGTransform.h"
#include "Engine/EngineInterface.h"


COGPhysics::COGPhysics(GameObject* pGO, bool bGenerateCollisionEvents)
	: Component(pGO)
	  , mTransform(nullptr), mBoxShape(nullptr), mCircleShape(nullptr), mController(nullptr), mSpeed(0), mDirection({0,0}),
	  mGenerateCollisionEvents(bGenerateCollisionEvents)
{
}

void COGPhysics::Initialize()
{
	// Get components
	mTransform = mGO->FindComponent<COGTransform>(ComponentType::Transform);
	mBoxShape = mGO->FindComponent<COGBoxShape>(ComponentType::BoxShape);
	mCircleShape = mGO->FindComponent<COGCircleShape>(ComponentType::CircleShape);

	// Get controller component from paddles
	if (mBoxShape != nullptr && mCircleShape == nullptr)
	{
		mController = mGO->FindComponent<COGController>(ComponentType::PlayerController);
		
		if (mController == nullptr){
			mController = mGO->FindComponent<COGController>(ComponentType::AIController);
		}
	}

	AddToComponentVector(mPhysicsComponents);
}


void COGPhysics::Destroy()
{
	RemoveFromComponentVector(mPhysicsComponents);
}

void COGPhysics::Update(float fDeltaT)
{
	// If the object is a paddle
	if (mBoxShape && mCircleShape == nullptr)
		OverrideDirection();		// Set direction from the controller

	SetBoundaries();

	// integrate velocity
	exVector2& myPosition = mTransform->GetPosition();

	myPosition.x += mDirection.x * mSpeed * fDeltaT;
	myPosition.y += mDirection.y * mSpeed * fDeltaT;

	// check collisions
	if (mGenerateCollisionEvents)
	{
		for (COGPhysics* pPhysicsOther : COGPhysics::mPhysicsComponents)
		{
			// do not collide with self
			if (pPhysicsOther == this)
			{
				continue;
			}

			// TODO - maybe have IsColliding produce a vector/struct that contains the normal and then pass that into OnCollision?
			exVector2 collisionNormal = { 1.0f, 0 };
			const bool bResult = IsColliding(pPhysicsOther, collisionNormal);

			if (bResult)
			{
				for (IPhysicsCollisionEvent* pCollisionEventListener : mCollisionEventListeners)
				{
					pCollisionEventListener->OnCollision(this, pPhysicsOther, collisionNormal);
				}
			}
		}
	}
}

bool COGPhysics::IsColliding(COGPhysics* pOther, exVector2 & nNormal)
{
	if (mCircleShape && pOther->mBoxShape )
	{
		const exVector2 posCircle = mTransform->GetPosition();
		const exVector2 posBox = pOther->mTransform->GetPosition();
		const float boxWidth = pOther->mBoxShape->Width();
		const float boxHeight = pOther->mBoxShape->Height();

		// Closest point to ball on the paddle
		float closestX = posCircle.x;							
		float closestY = posCircle.y;

		// When ball is at the left side of the rectangle
		if (posCircle.x < posBox.x){
			// Set closest x point on the rectangle as smallest x of rectangle
			closestX = posBox.x;								
		}
		
		// When ball is at the right side of the rectangle
		if (posCircle.x > posBox.x + boxWidth) {
			// Set closest x point on the rectangle as highest x of rectangle
			closestX = posBox.x + boxWidth;						
		}
		
		// When ball is at the top of the rectangle
		if (posCircle.y < posBox.y){
			// Set closest y point on the rectangle as smallest y of the rectangle
			closestY = posBox.y;								
			
		}
		// When ball is at the bottom of the rectangle
		if (posCircle.y > posBox.y + boxHeight){
			// Set closest y point on the rectangle as highest y of the rectangle
			closestY = posBox.y + boxHeight;					
		}
		
		// Get distance between closest point and ball's center
		const float distance = sqrt(pow(closestX - posCircle.x, 2) + pow(closestY - posCircle.y, 2)); 

		// Check for the collision by comparing distances
		if (distance < mCircleShape->Radius())
		{
			nNormal = { closestX - (posCircle.x - mDirection.x),  closestY - (posCircle.y - mDirection.y) };
			mTransform->SetPosition({ posCircle.x  , posCircle.y + pOther->mDirection.y * 10});
			return true;
		}

	}
	
	return false;
}

// Restrict gameobjects to viewport
void COGPhysics::SetBoundaries()
{
	const exVector2 position = mTransform->GetPosition();

	if (mCircleShape == nullptr && mBoxShape)											// Check for box shape
	{
		// Restrict paddle vertically to viewport boundaries
		if (position.y < 0){
			mTransform->SetPosition({position.x, 0});
		}												
		else if (position.y + mBoxShape->Height() > kViewportHeight){
			mTransform->SetPosition({ position.x, kViewportHeight - mBoxShape->Height() });
		}
	}
	// Check for circle shape
	else if (mCircleShape && mBoxShape == nullptr)										
	{
		if (position.y + mCircleShape->Radius() >= kViewportHeight)										
		{
			const exVector2 normal = { 0, -1 };																
			const float dotProdcut = mDirection.x * normal.x + mDirection.y * normal.y;						
			const exVector2 reflectNormal = { 2 * normal.x* dotProdcut, 2 * normal.y * dotProdcut };
			mTransform->SetPosition({ position.x - mDirection.x , position.y - mDirection.y });
			SetDirection({ mDirection.x - reflectNormal.x, mDirection.y - reflectNormal.y });	
		}

		// Check for top of the window
		if (position.y - mCircleShape->Radius() <= 0)													
		{
			const exVector2 normal = { 0, 1 };																
			const float dotProdcut = mDirection.x * normal.x + mDirection.y * normal.y;						
			const exVector2 reflectNormal = { 2 * normal.x* dotProdcut, 2 * normal.y * dotProdcut };
			mTransform->SetPosition({ position.x - mDirection.x , position.y - mDirection.y });			
			SetDirection({ mDirection.x - reflectNormal.x, mDirection.y - reflectNormal.y });			
		}

	}
}

// Change direction depending on the user input
void COGPhysics::OverrideDirection()
{
	if (mController)							// Check for a controller
	{
		mDirection = mController->GetDirection();		// Change direction
	}
}

void COGPhysics::AddCollisionEventListener(IPhysicsCollisionEvent* pEvent)
{
	mCollisionEventListeners.push_back(pEvent);
}

// Set velocity magnitude of the object
void COGPhysics::SetSpeed(float pSpeed)
{
	mSpeed = pSpeed;
}

// Set object normal direction
void COGPhysics::SetDirection(exVector2 nDirection)
{
	const float magnitude = sqrt(pow(nDirection.x, 2) + pow(nDirection.y, 2));		// Get velocity direction magnitude
	mDirection = magnitude == 0 ? exVector2{ 0, 0 } : exVector2{ nDirection.x / magnitude, nDirection.y / magnitude };
}

std::vector<COGPhysics*> COGPhysics::mPhysicsComponents;