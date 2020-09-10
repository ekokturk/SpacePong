//
// * ENGINE-X
// * SAMPLE GAME
//
// + Game.h
// definition of MyGame, an implementation of exGameInterface
//
#pragma once

#include "GameInterface.h"
#include "Engine/EngineTypes.h"
#include "World.h"

//-----------------------------------------------------------------
//-----------------------------------------------------------------

class MyGame : public exGameInterface
{
public:

	MyGame();
	virtual	~MyGame();

	virtual void Initialize( exEngineInterface* pEngine ) override;

	virtual const char*	 GetWindowName() const override;
	virtual void GetClearColor( exColor& color ) const override;

	virtual void OnEvent( SDL_Event* pEvent ) override;
	virtual void OnEventsConsumed() override;

	virtual void Run( float fDeltaT ) override;

private:


	void RenderBackground();
	void MainMenu();
	
	exEngineInterface* mEngine;

	bool isMainMenu;
	int mFontH1;
	int mFontH2;

	PlayerType mTypePlayer1;
	PlayerType mTypePlayer2;

	World *	 mWorld;

};
