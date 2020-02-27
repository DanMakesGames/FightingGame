#include "Master.h"

Master::Master() : graphicsModule(), assetManager(), currentGame()
{
}

bool Master::Initialize() 
{
	DEBUG_PRINT("Master Init");
	Object::master = this;

	if (!graphicsModule.Initialize(&assetManager))
		return false;

	// Could be initialized elsewhere in the future.
	currentGame.Initialize(this);
	return true;
}