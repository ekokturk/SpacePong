// Copyright (C) 2020, Eser Kokturk. All Rights Reserved.

#include <string>
#include "SDL.h"
#include "World.h"
#include "COGController.h"
#include "COGShape.h"
#include "COGPhysics.h"
#include "COGBounce.h"
#include "COGPlayerController.h"
#include "COGAIController.h"
#include "COGBoxShape.h"
#include "COGCircleShape.h"
#include "COGScore.h"
#include "COGTransform.h"


World::World(exEngineInterface* pEngine)
	: mEngine(pEngine)
	, mWinScore(10)
	, mPaddleWon(PaddleType::None)
{
}

GameObject* CreatePaddle(exEngineInterface * pEngine, PaddleType nPaddleType, ComponentType eControllerType)
{
	const float fPaddleWidth = 20.0f;
	const float fPaddleHeight = 100.0f;

	GameObject* pPaddle = new GameObject(pEngine);

	COGTransform* pTransform = new COGTransform(pPaddle);
	pPaddle->AddComponent(pTransform);

	COGBoxShape* pBoxShape = new COGBoxShape(pPaddle, fPaddleWidth, fPaddleHeight);
	
	// Set paddle color
	pBoxShape->SetColorMain({ 51,51,51,255 });												
	pPaddle->AddComponent(pBoxShape);

	COGPhysics* pPhysics = new COGPhysics(pPaddle, false);
	
	// Set paddle speed
	pPhysics->SetSpeed(250.0f);																
	pPaddle->AddComponent(pPhysics);

	// Paddle score component
	COGScore * pScore = new COGScore(pPaddle, nPaddleType);									
	pPaddle->AddComponent(pScore);

	// Setup for left paddle - Paddle 1
	if (nPaddleType == PaddleType::PaddleLeft)												
	{

		pTransform->SetPosition({ 50.0f, 120.0f });											
		if (eControllerType == ComponentType::PlayerController)								
		{
			COGPlayerController * pPlayerController = new COGPlayerController(pPaddle);		
			pPaddle->AddComponent(pPlayerController);
			pPlayerController->SetKeys(SDL_SCANCODE_W, SDL_SCANCODE_S);						
		}
		else																				
		{
			COGAIController * pAIController = new COGAIController(pPaddle);					
			pPaddle->AddComponent(pAIController);
		}
	}
	else if (nPaddleType == PaddleType::PaddleRight)										
	{
		pTransform->SetPosition({ 730.0f, 120.0f });
		if (eControllerType == ComponentType::PlayerController)								
		{
			COGPlayerController * pPlayerController = new COGPlayerController(pPaddle);		
			pPaddle->AddComponent(pPlayerController);
			pPlayerController->SetKeys(SDL_SCANCODE_UP, SDL_SCANCODE_DOWN);					
		}
		else																			
		{
			COGAIController * pAIController = new COGAIController(pPaddle);					
			pPaddle->AddComponent(pAIController);
		}
	}

	pPaddle->Initialize();

	return pPaddle;
}

// create ball (notice how it will generate events)
GameObject* CreateBall(exEngineInterface * pEngine, exVector2 nPosition)
{
	const float fBallRadius = 12.0f;

	GameObject* pBall = new GameObject(pEngine);

	COGTransform* pTransform = new COGTransform(pBall);
	pTransform->SetPosition(nPosition);											// Set ball position
	pBall->AddComponent(pTransform);

	COGCircleShape* pCircleShape = new COGCircleShape(pBall, fBallRadius);
	pCircleShape->SetColorMain({ 255,0,0,180 });								// Set ball color
	pBall->AddComponent(pCircleShape);

	COGPhysics* pPhysics = new COGPhysics(pBall, true);
	pPhysics->SetSpeed(450.0f);													// Set ball speed
	pPhysics->SetDirection({1.0f, -.5f});										// Set ball direction
	pBall->AddComponent(pPhysics);

	COGBounce* pBounce = new COGBounce(pBall);
	pBall->AddComponent(pBounce);

	pBall->Initialize();

	return pBall;
}


// Create gameobjects
void World::Create(PlayerType eType1, PlayerType eType2)
{
	ComponentType controllerP1;								// Controller component for paddle 1
	ComponentType controllerP2;								// Controller component for paddle 2
	// Check for controller type and then assign component depending on AI or Player
	if (eType1 == PlayerType::PlayerHumanType)
		controllerP1 = ComponentType::PlayerController;
	else
		controllerP1 = ComponentType::AIController;

	if (eType2 == PlayerType::PlayerHumanType)
		controllerP2 = ComponentType::PlayerController;
	else
		controllerP2 = ComponentType::AIController;

	// Create gameobjects
	mGameObjects.push_back(CreatePaddle(mEngine, PaddleType::PaddleLeft, controllerP1));
	mGameObjects.push_back(CreatePaddle(mEngine, PaddleType::PaddleRight, controllerP2));
	mGameObjects.push_back(CreateBall(mEngine, { kViewportWidth/2, kViewportHeight/2}));

	// Initialize game world
	Initialize();
}

// Initialize world
void World::Initialize()
{
	// Setup the target that AI fallows
	for ( COGController* pController : COGController::mControllerComponents)
	{
		if(COGAIController * pAIController = dynamic_cast<COGAIController*>(pController))
		{
			// Search gameobjects for the ball
			for (GameObject* gameObject : mGameObjects)
			{
				if (gameObject->FindComponent<COGShape>(ComponentType::CircleShape))
					pAIController->SetTarget(gameObject->FindComponent<COGTransform>(ComponentType::Transform));
			}
		}
	}
}

void World::Destroy()
{
	for (GameObject* pGameObject : mGameObjects)
	{
		delete pGameObject;
	}
	mGameObjects.clear();
}

void World::Update(float fDeltaT)
{
	// If anyone is victorious
	if (mPaddleWon != PaddleType::None)			
	{
		RenderResult();	
		return;
	}


	// run simulation first
	for (COGPhysics* pPhysics : COGPhysics::mPhysicsComponents)
	{
		pPhysics->Update(fDeltaT);
	}

	// then render everything
	for (COGShape* pShape : COGShape::mShapeComponents)
	{
		pShape->Render();
	}

	// Check for score components
	for (COGScore * pScore : COGScore::mScoreComponents)
	{
		RenderScore(pScore->GetPaddleType(), pScore->Score());												

		for (GameObject* pGameObject : mGameObjects)														
		{
			if (pGameObject->FindComponent<COGCircleShape>(ComponentType::CircleShape))		
			{
				// Check if paddle is scored depending on the ball location and increment score
				const bool IsScored = pScore->CheckForScore(pGameObject);												
				if (IsScored)																				
				{
					mPaddleWon = pScore->GetWinner(mWinScore);												
					// Reset ball
					pGameObject->FindComponent<COGTransform>(ComponentType::Transform)->SetPosition({ kViewportWidth / 2,  kViewportHeight / 2 });
					COGPhysics * physics = pGameObject->FindComponent<COGPhysics>(ComponentType::Physics);
					physics->SetDirection({ -physics->Direction().x, physics->Direction().y *0.5f});
				}
			}
		}
	}

}

// Render match score for a certain paddle
void World::RenderScore(PaddleType nPaddleType, int nScore)
{
	if(nPaddleType == PaddleType::PaddleLeft){
		mEngine->DrawText(0, { kViewportWidth / 2 - 90, 100 }, std::to_string(nScore).c_str(), { 255,255,255 }, 0);
	}
	else if (nPaddleType == PaddleType::PaddleRight){
		mEngine->DrawText(0, { kViewportWidth / 2 + 90, 100 }, std::to_string(nScore).c_str(), { 255,255,255 }, 0);
	}
	mEngine->DrawText(0, { kViewportWidth / 2 , 100 }, "-", { 255,255,255 }, 0);
}

// Render match results
void World::RenderResult()
{
	
	mEngine->DrawBox({ kViewportWidth / 2 - 200, kViewportHeight / 2 - 110 }, { kViewportWidth / 2 + 200 , kViewportHeight / 2 + 110 }, { 51,51,51,200 }, 0);
	mEngine->DrawText(0, { kViewportWidth / 2 - 80, kViewportHeight / 2 - 80 }, "VICTORY", { 255,255,255 }, 0);
	mEngine->DrawText(0, { kViewportWidth / 2 - 40, kViewportHeight / 2 - 20 }, "FOR", { 255,255,255 }, 0);
	mEngine->DrawText(0, { kViewportWidth / 2 - 80, kViewportHeight / 2 + 40 }, ("Player " + std::to_string((int)mPaddleWon)).c_str(), { 255,255,255 }, 0);
}


