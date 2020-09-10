// Copyright (C) 2020, Eser Kokturk. All Rights Reserved.

#include <random>
#include "COGBounce.h"
#include "COGPhysics.h"

COGBounce::COGBounce(GameObject* pGO)
	: Component(pGO)
{
}

void COGBounce::Initialize()
{
	COGPhysics* pPhysics = mGO->FindComponent<COGPhysics>(ComponentType::Physics);
	pPhysics->AddCollisionEventListener(this);
}

void COGBounce::OnCollision(COGPhysics* pMe, COGPhysics* pOther, exVector2 normal)
{
	// r = d - 2 * (d . n) n -> reflection vector formula
	const float magNormal = sqrt(pow(normal.x, 2) + pow(normal.y, 2));
	// Normalize normal vector
	normal = { normal.x / magNormal , normal.y / magNormal };											

	// Calculate the dot product vector between normal vector and ball velocity
	const float dotProdcut = pMe->Direction().x * normal.x + pMe->Direction().y  * normal.y;
	// Calculate the reflection vector
	const exVector2 reflectNormal = { 2 * normal.x* dotProdcut, 2 * normal.y * dotProdcut };					

	std::random_device rd;
	std::mt19937 mt(rd());
	const std::uniform_int_distribution<int> reflectRand(-10, 10);
	const int randomReflect = reflectRand(mt);

	// Add a random vertical velocity to the ball depending the paddle motion so that you have more control over the reflection
	pMe->SetDirection({ pMe->Direction().x - reflectNormal.x,  pMe->Direction().y + pOther->Direction().y / (2.0f + randomReflect / 10) - reflectNormal.y });
}