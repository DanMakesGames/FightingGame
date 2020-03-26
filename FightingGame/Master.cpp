#include "Master.h"
#include "Asset.h"
Master::Master() : graphicsModule(), assetManager(), currentGame()
{
}

bool Master::Initialize() 
{
	DEBUG_PRINT("Master Init");

	// Establish Master Access.
	Object::master = this;
	Asset::master = this;
	
	if (!graphicsModule.Initialize(&assetManager))
		return false;

	// Could be initialized elsewhere in the future.
	currentGame.Initialize(this);
	return true;
}