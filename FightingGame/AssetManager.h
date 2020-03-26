#pragma once

#include "Core.h"
#include "Asset.h"
#include "StaticModelAsset.h"
#include "TextureAsset.h"
#include "MaterialAsset.h"
#include <unordered_map>



/*
Handles the pre-loading, and storage of loaded assets.

Usage of linked lists for storing assets should ensure pointer safety.
TODO: If the LoadAsset search takes too long, create a unordered_map linking source name and assetPointer.

Only 1 should exist at a time or else things will get weird due to static references. Shouldn't be a problem.
*/
class AssetManager
{
public:

	// Request and asset to be loaded.
	// looks for asset. If not found it loads the asset from the source.
	// If error occurs, return nullptr.
	const void* LoadAsset(const string& source, Asset::EAssetType type);

private:

	std::unordered_map<string, void*> sourceToPtrMap;
	// storage of assets. A new category will need to be created for each asset type
	std::list<StaticModelAsset> staticModels;
	//std::vector<SkeletalModelAsset> skeletalModels;
	std::list<TextureAsset> textures;
	std::list<MaterialAsset> materials;
	template<class T>
	void* GetOrLoad(const string& source,const Asset::EAssetType& type, std::list<T>& assetList,std::unordered_map<string,void*>& srcToPtrMap);

};

