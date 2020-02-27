#pragma once
#include "Core.h"
#include "GraphicsModule.h"
#include "NetworkModule.h"
#include "Game.h"
#include "AssetManager.h"

/*
Idk im putting everything in here and no one can stop me.
Everything needed to exectute runtime gameplay.
*/
class Master
{
public:
	Master();
	AssetManager assetManager;
	NetworkModule netModule;
	GraphicsModule graphicsModule;
	Game currentGame;
	bool Initialize();
};

