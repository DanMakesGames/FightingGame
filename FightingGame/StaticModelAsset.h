#pragma once
#include "PrimitiveAsset.h"
#include "Mesh.h"
/*
Just meshes and materials
*/
class StaticModelAsset : public PrimitiveAsset
{
public:
	bool InitializeMeshesFromScene(const aiScene* scene);
private:
	std::vector<Mesh> meshes;

};

