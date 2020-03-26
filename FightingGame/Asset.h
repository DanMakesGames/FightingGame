#pragma once
#include "Core.h"

class Master;
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
	enum class EAssetType
	{
		AT_STATIC_MODEL,
		AT_SKELETAL_MODEL,
		AT_TEXTURE,
		AT_MATERIAL,
		AT_SOUND
	};

	Asset(string inSource, EAssetType inType);

	virtual bool LoadFromFile(std::string fileName) = 0;

	string GetSource();
	void SetSource(string sourceName);

	// Master access. Allows access to the owning assetManager in particular.
	static Master* master;

private:

	// the file name of the asset.
	std::string source;
	EAssetType type;
};

