#pragma once
#include "PrimitiveAsset.h"
#include "MeshAsset.h"
/*
Just meshes and materials
*/
class StaticModelAsset : public PrimitiveAsset
{
public:
	using PrimitiveAsset::PrimitiveAsset;
	bool LoadFromFile(std::string fileName);

	const MeshAsset* GetMeshAssets(uint& count);

private:
	bool InitializeMeshesFromScene(const aiScene* scene);
	std::vector<MeshAsset> meshAssets;

};

