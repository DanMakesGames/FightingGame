#pragma once
#include "GameState.h"
//#include "Master.h"

class Master;
/**
The base class for a session of the game. Created when a new match starts 
and containts all the info needed to run/manage the gamestate.
**/

class Game
{
public:
	Game();
	void Initialize(Master* inMaster);

	void MainLoop();

	bool AdvanceFrame(int flags);

	void Tick();
	
	GameState gameState;

private:

	// online ggpo stuff
	bool bIsOnline;

	Master* master;
};

