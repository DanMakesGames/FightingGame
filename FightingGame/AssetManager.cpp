#include "AssetManager.h"

const void* AssetManager::LoadAsset(const string& source, Asset::EAssetType type)
{
	void* assetPointer = nullptr;
	switch (type)
	{
	case Asset::EAssetType::AT_STATIC_MODEL:
	{	
		assetPointer = GetOrLoad<StaticModelAsset>(source, type, staticModels, sourceToPtrMap);
	}
	break;
	case Asset::EAssetType::AT_TEXTURE:
	{
		assetPointer = GetOrLoad<TextureAsset>(source, type, textures, sourceToPtrMap);
	}
	break;
	}

	return assetPointer;
}

template<class T>
void* AssetManager::GetOrLoad(const string& source, const Asset::EAssetType& type, std::list<T>& assetList, std::unordered_map<string, void*>& srcToPtrMap)
{
	void* assetPointer = nullptr;
	try
	{
		assetPointer = srcToPtrMap.at(source);
		DEBUG_PRINT("AM: ASSET "<<source<<" FOUND");
	}
	catch (const std::out_of_range& oor)
	{
		// no mapping for this source. Must Load new asset.
		DEBUG_PRINT("AM: ASSET NOT FOUND, loading now: " << source);

		assetList.emplace_back(source, type);
		assetList.back().LoadFromFile(source);
		assetPointer = &assetList.back();

		srcToPtrMap.emplace(source, assetPointer);
	}

	return assetPointer;
}