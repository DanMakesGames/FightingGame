#pragma once
#include "Asset.h"
#include <Magick++.h>

struct TextureData
{
	const void* data;
	uint width;
	uint height;
};

class TextureAsset : public Asset
{
public:

	using Asset::Asset;
	bool LoadFromFile(std::string fileName);

	TextureData GetTextureData() const;
	
private:
	Magick::Blob texBlob;
	uint width, height;
};

