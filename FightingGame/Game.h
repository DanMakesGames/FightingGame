#pragma once
#include "GameState.h"
/**
The base class for a session of the game. Created when a new match starts 
and containts all the info needed to run/manage the gamestate.
**/

class Game
{
public:

	void Initialize();

	int MainLoop();

	bool AdvanceFrame(int flags);

	int Tick();
	
	GameState gameState;

private:

	// online ggpo stuff
	bool bIsOnline;
};

