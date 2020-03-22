#include <iostream>
#include <fstream> 
#include <string>
#include "AssetManager.h"
#include "NetworkModule.h"
#include "GraphicsModule.h"
#include "Master.h"
#include "Magick++.h"


using namespace std;

int main(int argc, char** argv) 
{

	Master master;
	master.Initialize();
	master.currentGame.MainLoop();

	return 0;
}