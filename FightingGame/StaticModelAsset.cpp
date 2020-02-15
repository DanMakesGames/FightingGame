#include "StaticModelAsset.h"

bool StaticModelAsset::InitializeMeshesFromScene(const aiScene* scene)
{
	if (!scene->HasMeshes())
		return true;
	meshes.clear();
	meshes.resize(scene->mNumMeshes);
	// loop over meshes setting each one up
	for (int meshIndex = 0; meshIndex < scene->mNumMeshes; meshIndex++)
	{
		//meshes.emplace_back();
		DEBUG_PRINT("Name:" << scene->mMeshes[meshIndex]->mName.C_Str() << "Tex ID: " << scene->mMeshes[meshIndex]->mMaterialIndex);
		meshes[meshIndex].InitMesh(meshIndex, scene->mMeshes[meshIndex]);
	}
}