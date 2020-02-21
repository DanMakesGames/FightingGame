#include "AssetManager.h"

const void* AssetManager::LoadAsset(string source, Asset::EAssetType type)
{
	void* assetPointer = nullptr;
	switch (type)
	{
	case Asset::EAssetType::AT_STATIC_MODEL:
		{
			try
			{
				assetPointer = sourceToPtrMap.at(source);
			}
			catch (const std::out_of_range & oor)
			{
				// no mapping for this source. Must Load new asset.
				DEBUG_PRINT("AM. NOT FOUND, loading now: "<< source);

				staticModels.emplace_back(source, type);
				staticModels.back().LoadFromFile(source);
				assetPointer = &staticModels.back();
			}
		}
		break;
	}

	return assetPointer;
}