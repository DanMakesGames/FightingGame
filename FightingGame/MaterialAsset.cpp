#include "Master.h"
#include "MaterialAsset.h"
#include <fstream>

MaterialAsset::MaterialAsset(string inSource, EAssetType inType) : Asset(inSource,inType), data()
{
}


bool MaterialAsset::LoadFromFile(std::string fileName)
{
	// open and read file.
	std::ifstream matFile(fileName.c_str());
	
	if (matFile.fail())
	{
		fprintf(stderr,"Error: Could not load material file %s\n", fileName.c_str());
		return false;
	}


	std::string line;
	while (getline(matFile, line))
	{
		// parse line.
		char str[MAX_MAT_FILE_ELEM_LENGTH];
		strcpy(str, line.c_str());
		char* ident = strtok(str, MAT_FILE_DELIM);
		char* elements[MAX_MAT_FILE_ELEMENTS] = { NULL };

		// load elements
		for (int elemIndex = 0; elemIndex < MAX_MAT_FILE_ELEMENTS; elemIndex++)
		{
			elements[elemIndex] = strtok(NULL, MAT_FILE_DELIM);
		}

		// match with identifier, and extract data
		if (strcmp(ident, TEXTURE_IDENT) == 0)
		{
			data.texture = (TextureAsset*)master->assetManager.LoadAsset(string(elements[0]), Asset::EAssetType::AT_TEXTURE);

			if (data.texture == nullptr)
			{
				fprintf(stderr, "Error: error loading texture for material %s\n", fileName);
				return false;
			}
		}
		else if (strcmp(ident, AMBIENT_IDENT) == 0)
		{

		}
		else if (strcmp(ident, DIFFUSE_IDENT) == 0)
		{
		}
		else if (strcmp(ident, SPECULAR_IDENT) == 0)
		{
		}
		else if (strcmp(ident, SHININESS_IDENT) == 0)
		{
		}
	}

	// invalid file if no texture definition was given
	if (data.texture == nullptr)
	{
		fprintf(stderr, "Error: Material file format wrong. No texture given.\n");
		return false;
	}

	return true;
}

const MaterialAsset::MaterialData&  MaterialAsset::GetData()
{
	return data;
}