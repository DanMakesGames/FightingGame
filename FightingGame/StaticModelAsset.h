#pragma once
#include "PrimitiveAsset.h"
#include "MeshAsset.h"
/*
Just meshes and materials
*/
class StaticModelAsset : public PrimitiveAsset
{
public:
	bool LoadFromFile(std::string fileName);

private:
	bool InitializeMeshesFromScene(const aiScene* scene);
	std::vector<MeshAsset> meshAssets;

};

