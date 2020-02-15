#pragma once
#include "Core.h"
/*
Responsibilites: Loading the asset from file. Storing the asset's information.

an asset of some kind. Pretty much anything that needs to be loaded at runtime.
Anything that benefits from reuse/pre-loading.
code for drawning assets is included within the component class, not the GraphicsModule class
or the asset class. This also allows for different assets to be combined to make new graphical
effect without needing to make both a new assetType, and a new component type.
This is a logical and OO means of handling responsibility. Calls to draw do pass through 
the GraphicsModule, allowing the GraphicsModule to preform any necessary organizing.
Passing through the GraphicsModule also could facilitate instanced drawing.

*/
class Asset
{
public:
	virtual bool LoadFromFile(std::string fileName) = 0;
private:
	std::string name;

	// the file name of the asset.
	std::string assetSource;
};

