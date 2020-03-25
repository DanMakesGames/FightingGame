#pragma once
#include "Core.h"
#include "Asset.h"
#include "TextureAsset.h"

// Properties of Material file format 
// maximum length of any element in an material file
#define MAX_MAT_FILE_ELEM_LENGTH 20
#define MAX_MAT_FILE_ELEMENTS 6
#define MAT_FILE_DELIM " "
#define TEXTURE_IDENT "texture"
#define AMBIENT_IDENT "ambient"
#define DIFFUSE_IDENT "diffuse"
#define SPECULAR_IDENT "specular"
#define SHININESS_IDENT "shininess"

// Default material values
#define AMBIENT_DEFAULT glm::vec3(0,0,0)
#define DIFFUSE_DEFAULT glm::vec3(0,0,0)
#define SPECULAR_DEFAULT glm::vec3(0,0,0)
#define SHININESS_DEFAULT 0

// because making your own file formats is cool.
// leave me alone.
class MaterialAsset : public Asset
{
public:

	MaterialAsset(string inSource, EAssetType inType);
	bool LoadFromFile(std::string fileName);

	struct MaterialData
	{
		TextureAsset* texture;
		glm::vec3 ambient;
		glm::vec3 diffuse;
		glm::vec3 specular;
		float shininess;
		MaterialData() : 
			texture(nullptr), 
			ambient(AMBIENT_DEFAULT),
			diffuse(DIFFUSE_DEFAULT),
			specular(SPECULAR_DEFAULT),
			shininess(SHININESS_DEFAULT)
		{}
	};

	const MaterialData& GetData();

private:
	MaterialData data;
};

