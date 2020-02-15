#pragma once

#include "Asset.h"
#include "StaticModelAsset.h"
#include "TextureAsset.h"

/*
Handles the pre-loading, and storage of loaded assets.
*/
class AssetManager
{
public:
private:
	// storage of assets. A new category will need to be created for each asset type
	std::vector<StaticModelAsset> staticModels;
	//std::vector<SkeletalModelAsset> skeletalModels;
	std::vector<TextureAsset> textures;

};

