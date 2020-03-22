#include "TextureAsset.h"



bool TextureAsset::LoadFromFile(std::string fileName)
{
	try 
	{
		Magick::Image tempImage(fileName);
		tempImage.write(&texBlob, "RGBA");
		width = tempImage.columns();
		height = tempImage.rows();
	}
	catch (Magick::Error& error)
	{
		std::cerr << "Error Loading Texture " << fileName << ": " << error.what() << std::endl;
		return false;
	}
	
	return true;
}

TextureData TextureAsset::GetTextureData() const
{
	TextureData returnData;
	returnData.data = texBlob.data();
	returnData.width = width;
	returnData.height = height;

	return returnData;
}