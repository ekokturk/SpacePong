//
// * ENGINE-X
// * SAMPLE GAME
//
// + Game.cpp
// implementation of MyGame, an implementation of exGameInterface
//

#include "Game.h"
#include "World.h"

#include "Engine/EngineInterface.h"
#include "SDL.h"

//-----------------------------------------------------------------
//-----------------------------------------------------------------

const char* gWindowName = "Sample EngineX Game";

//-----------------------------------------------------------------
//-----------------------------------------------------------------

MyGame::MyGame()
	: mEngine(nullptr)
	  , isMainMenu(true)
	  , mFontH1(0)
	  , mFontH2(0)
	  , mWorld(nullptr)
{
}

//-----------------------------------------------------------------
//-----------------------------------------------------------------

MyGame::~MyGame()
{
}

//-----------------------------------------------------------------
//-----------------------------------------------------------------

void MyGame::Initialize( exEngineInterface* pEngine )
{
	mEngine = pEngine;


	mFontH1 = mEngine->LoadFont("GALACTIC.ttf", 32);
	mFontH2 = mEngine->LoadFont("GALACTIC.ttf", 22);

}

//-----------------------------------------------------------------
//-----------------------------------------------------------------

const char* MyGame::GetWindowName() const
{
	return gWindowName;
}

//-----------------------------------------------------------------
//-----------------------------------------------------------------

void MyGame::GetClearColor( exColor& color ) const
{
	color.mColor[0] = 0;
	color.mColor[1] = 0;
	color.mColor[2] = 0;
}

//-----------------------------------------------------------------
//-----------------------------------------------------------------

void MyGame::OnEvent( SDL_Event* pEvent )
{
}

//-----------------------------------------------------------------
//-----------------------------------------------------------------

void MyGame::OnEventsConsumed()
{
	int nKeys = 0;
	const Uint8 *pState = SDL_GetKeyboardState( &nKeys );

}

//-----------------------------------------------------------------
//-----------------------------------------------------------------

void MyGame::Run( float fDeltaT )
{
	RenderBackground();													// Show background

	if(isMainMenu)														// Show main menu
		MainMenu();

	if(mWorld != nullptr)												// Show world
		mWorld->Update(fDeltaT);

	if (SDL_GetKeyboardState(0)[SDL_SCANCODE_ESCAPE] && !isMainMenu)	// Escape command which returns to main menu
	{
		mWorld->Destroy();
		mWorld = nullptr;
		isMainMenu = true;
	}

}


void MyGame::RenderBackground()
{
	// Earth
	mEngine->DrawCircle({ kViewportWidth / 2, kViewportHeight / 2 }, 350.0f, { 0,18,65,90 }, 10);
	mEngine->DrawCircle({ kViewportWidth / 2, kViewportHeight / 2 }, 280.0f, { 0,18,45,120 }, 10);
	mEngine->DrawCircle({ kViewportWidth / 2, kViewportHeight / 2 }, 200.0f, { 0,18,45,180 }, 10);
	mEngine->DrawCircle({ kViewportWidth / 2, kViewportHeight / 2 }, 150.0f, { 0,18,105,100 }, 10);
	mEngine->DrawCircle({ kViewportWidth / 2 - 3, kViewportHeight / 2 - 3 }, 121.0f, { 0,38,140,255 }, 9);
	mEngine->DrawCircle({ kViewportWidth / 2, kViewportHeight / 2 }, 120.0f, { 4,38,100,255 }, 9);

	// America
	mEngine->DrawCircle({ kViewportWidth / 2 - 50, kViewportHeight / 2 - 40 }, 30.0f, { 24,130,47,255 }, 9);
	mEngine->DrawCircle({ kViewportWidth / 2 - 33, kViewportHeight / 2 - 62 }, 20.0f, { 24,130,47,255 }, 9);
	mEngine->DrawCircle({ kViewportWidth / 2 - 65, kViewportHeight / 2 - 66 }, 20.0f, { 24,130,47,255 }, 9);
	mEngine->DrawCircle({ kViewportWidth / 2 - 60, kViewportHeight / 2 - 20 }, 20.0f, { 24,130,47,255 }, 9);
	mEngine->DrawCircle({ kViewportWidth / 2 - 55, kViewportHeight / 2 }, 10.0f, { 24,130,47,255 }, 9);
	mEngine->DrawCircle({ kViewportWidth / 2 - 31, kViewportHeight / 2 + 24 }, 30.0f, { 24,130,47,255 }, 9);
	mEngine->DrawCircle({ kViewportWidth / 2 - 31, kViewportHeight / 2 + 24 }, 30.0f, { 24,130,47,255 }, 9);
	mEngine->DrawCircle({ kViewportWidth / 2 - 29, kViewportHeight / 2 + 44 }, 20.0f, { 24,130,47,255 }, 9);
	mEngine->DrawCircle({ kViewportWidth / 2 - 29, kViewportHeight / 2 + 54 }, 15.0f, { 24,130,47,255 }, 9);
	mEngine->DrawCircle({ kViewportWidth / 2 - 29, kViewportHeight / 2 + 64 }, 10.0f, { 24,130,47,255 }, 9);

	// Greenland
	mEngine->DrawCircle({ kViewportWidth / 2 + 0, kViewportHeight / 2 - 100 }, 10.0f, { 255,255,255,255 }, 9);
	mEngine->DrawCircle({ kViewportWidth / 2 + 5, kViewportHeight / 2 - 90 }, 10.0f, { 255,255,255,255 }, 9);
	mEngine->DrawCircle({ kViewportWidth / 2 + 20, kViewportHeight / 2 - 95 }, 15.0f, { 255,255,255,255 }, 9);
	mEngine->DrawCircle({ kViewportWidth / 2 + 15, kViewportHeight / 2 - 75 }, 15.0f, { 255,255,255,255 }, 9);
	mEngine->DrawCircle({ kViewportWidth / 2 + 15, kViewportHeight / 2 - 65 }, 10.0f, { 255,255,255,255 }, 9);

	// Africa
	mEngine->DrawCircle({ kViewportWidth / 2 + 70, kViewportHeight / 2 + 10 }, 30.0f, { 24,130,47,255 }, 9);
	mEngine->DrawCircle({ kViewportWidth / 2 + 85, kViewportHeight / 2 + 10 }, 30.0f, { 24,130,47,255 }, 9);
	mEngine->DrawCircle({ kViewportWidth / 2 + 90, kViewportHeight / 2 + 30 }, 20.0f, { 24,130,47,255 }, 9);
	mEngine->DrawCircle({ kViewportWidth / 2 + 110, kViewportHeight / 2 - 10 }, 10.0f, { 24,130,47,255 }, 9);
	mEngine->DrawCircle({ kViewportWidth / 2 + 85, kViewportHeight / 2 + 50 }, 15.0f, { 24,130,47,255 }, 9);
	mEngine->DrawCircle({ kViewportWidth / 2 + 75, kViewportHeight / 2 + 60 }, 10.0f, { 24,130,47,255 }, 9);

	// Europe
	mEngine->DrawCircle({ kViewportWidth / 2 + 50, kViewportHeight / 2 - 40 }, 10.0f, { 24,130,47,255 }, 9);
	mEngine->DrawCircle({ kViewportWidth / 2 + 70, kViewportHeight / 2 - 50 }, 15.0f, { 24,130,47,255 }, 9);
	mEngine->DrawCircle({ kViewportWidth / 2 + 80, kViewportHeight / 2 - 60 }, 20.0f, { 24,130,47,255 }, 9);
	mEngine->DrawCircle({ kViewportWidth / 2 + 95, kViewportHeight / 2 - 40 }, 15.0f, { 24,130,47,255 }, 9);
	mEngine->DrawCircle({ kViewportWidth / 2 + 90, kViewportHeight / 2 - 55 }, 15.0f, { 24,130,47,255 }, 9);
	mEngine->DrawCircle({ kViewportWidth / 2 + 50, kViewportHeight / 2 - 60 }, 5.0f, { 24,130,47,255 }, 9);

	// Nordic
	mEngine->DrawCircle({ kViewportWidth / 2 + 60, kViewportHeight / 2 - 90 }, 10.0f, { 24,130,47,255 }, 9);
	mEngine->DrawCircle({ kViewportWidth / 2 + 60, kViewportHeight / 2 - 80 }, 5.0f, { 24,130,47,255 }, 9);

	// Antartica
	mEngine->DrawCircle({ kViewportWidth / 2 - 20, kViewportHeight / 2 + 107 }, 5.0f, { 255,255,255,255 }, 9);
	mEngine->DrawCircle({ kViewportWidth / 2 - 15, kViewportHeight / 2 + 107 }, 8.0f, { 255,255,255,255 }, 9);
	mEngine->DrawCircle({ kViewportWidth / 2 - 10, kViewportHeight / 2 + 107 }, 10.0f, { 255,255,255,255 }, 9);
	mEngine->DrawCircle({ kViewportWidth / 2 - 5, kViewportHeight / 2 + 108 }, 10.0f, { 255,255,255,255 }, 9);
	mEngine->DrawCircle({ kViewportWidth / 2 + 0, kViewportHeight / 2 + 108 }, 10.0f, { 255,255,255,255 }, 9);
	mEngine->DrawCircle({ kViewportWidth / 2 + 15, kViewportHeight / 2 + 107 }, 10.0f, { 255,255,255,255 }, 9);
	mEngine->DrawCircle({ kViewportWidth / 2 + 15, kViewportHeight / 2 + 105 }, 10.0f, { 255,255,255,255 }, 9);
	mEngine->DrawCircle({ kViewportWidth / 2 + 20, kViewportHeight / 2 + 105 }, 7.0f, { 255,255,255,255 }, 9);
	mEngine->DrawCircle({ kViewportWidth / 2 + 25, kViewportHeight / 2 + 107 }, 5.0f, { 255,255,255,255 }, 9);
}


// Main menu screen of the game where you select the game mod
void MyGame::MainMenu()
{
	bool correctInput = false;		// Check for the correct keyboard input

	// Create Menu text
	mEngine->DrawBox({ kViewportWidth / 2 - 220, kViewportHeight / 2 - 220 }, { kViewportWidth / 2 + 220 , kViewportHeight / 2 + 220 }, { 51,51,51,200 }, 0);
	mEngine->DrawText(mFontH1, { kViewportWidth / 2 - 170, kViewportHeight / 2 - 150 }, "SELECT PLAYERS", { 255,255,255 }, 0);
	mEngine->DrawText(mFontH2, { kViewportWidth / 2 - 130, kViewportHeight / 2 - 50 }, "F1 - HUMAN vs HUMAN", { 255,255,255 }, 0);
	mEngine->DrawText(mFontH2, { kViewportWidth / 2 - 120, kViewportHeight / 2 }, "F2 - HUMAN vs AI", { 255,255,255 }, 0);
	mEngine->DrawText(mFontH2, { kViewportWidth / 2 - 110, kViewportHeight / 2 + 50 }, "F3 - AI vs HUMAN", { 255,255,255 }, 0);
	mEngine->DrawText(mFontH2, { kViewportWidth / 2 - 100, kViewportHeight / 2 + 100 }, "F4 - AI vs AI", { 255,255,255 }, 0);

	// Press F2 for Player 1 - Human vs Player 2 - Human 
	if (SDL_GetKeyboardState(0)[SDL_SCANCODE_F1])
	{
		mTypePlayer1 = PlayerType::PlayerHumanType;
		mTypePlayer2 = PlayerType::PlayerHumanType;
		correctInput = true;
	}
	// Press F2 for Player 1 - Human vs Player 2 - AI 
	else if (SDL_GetKeyboardState(0)[SDL_SCANCODE_F2])
	{
		mTypePlayer1 = PlayerType::PlayerHumanType;
		mTypePlayer2 = PlayerType::PlayerAIType;
		correctInput = true;
	}
	// Press F3 for Player 1 - AI vs Player 2 - Human 
	else if (SDL_GetKeyboardState(0)[SDL_SCANCODE_F3])
	{
		mTypePlayer1 = PlayerType::PlayerAIType;
		mTypePlayer2 = PlayerType::PlayerHumanType;
		correctInput = true;
	}
	// Press F2 for Player 1 - AI vs Player 2 - Human 
	else if (SDL_GetKeyboardState(0)[SDL_SCANCODE_F4])
	{
		mTypePlayer1 = PlayerType::PlayerAIType;
		mTypePlayer2 = PlayerType::PlayerAIType;
		correctInput = true;
	}

	// If the keyboard input is correct
	if (correctInput)
	{
		mWorld = new World(mEngine);
		mWorld->Create(mTypePlayer1, mTypePlayer2);
		isMainMenu = false;
	}
}




