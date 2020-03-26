#include "Master.h"
#include "MaterialAsset.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
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
		DEBUG_PRINT("read line: "<<line);

		// parse line.
		char* str = (char*)malloc( line.size() + 1);
		char strSize = line.size() + 1;
		strcpy_s(str, strSize,line.c_str());

		char* nextToken;
		char* ident = strtok_s(str, MAT_FILE_DELIM, &nextToken);

		// load elements
		char* elements[MAX_MAT_FILE_ELEMENTS] = { NULL };
		for (int elemIndex = 0; elemIndex < MAX_MAT_FILE_ELEMENTS; elemIndex++)
		{
			elements[elemIndex] = strtok_s(NULL, MAT_FILE_DELIM, &nextToken);
		}

		// match with identifier, and extract data
		if (strcmp(ident, TEXTURE_IDENT) == 0)
		{
			data.texture = (TextureAsset*)master->assetManager.LoadAsset(string(elements[0]), Asset::EAssetType::AT_TEXTURE);

			if (data.texture == nullptr)
			{
				fprintf(stderr, "Error: error loading texture %s for material %s\n", elements[0], fileName.c_str());
				return false;
			}
		}
		else if (strcmp(ident, AMBIENT_IDENT) == 0)
		{
			data.ambient = glm::vec3(stof(elements[0]), stof(elements[1]), stof(elements[2]));
		}
		else if (strcmp(ident, DIFFUSE_IDENT) == 0)
		{
			data.diffuse = glm::vec3(stof(elements[0]), stof(elements[1]), stof(elements[2]));
		}
		else if (strcmp(ident, SPECULAR_IDENT) == 0)
		{
			data.specular = glm::vec3(stof(elements[0]), stof(elements[1]), stof(elements[2]));
		}
		else if (strcmp(ident, SHININESS_IDENT) == 0)
		{
			data.shininess = std::stof(elements[0]);
		}
		free(str);
	}

	return true;
}

const MaterialAsset::MaterialData&  MaterialAsset::GetData() const
{
	return data;
}