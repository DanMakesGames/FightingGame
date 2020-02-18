#include "StaticModelAsset.h"

bool StaticModelAsset::LoadFromFile(std::string fileName)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(fileName, ASSIMP_STATIC_MODEL_IMPORT_SETTINGS);

	if (strcmp(importer.GetErrorString(), "") != 0)
	{
		fprintf(stderr,"ERROR: %s\n", importer.GetErrorString());
		delete scene;
		return  false;
	}

	InitializeMeshesFromScene(scene);

	//delete scene;
	return true;
}

bool StaticModelAsset::InitializeMeshesFromScene(const aiScene* scene)
{
	if (!scene->HasMeshes())
		return true;

	meshAssets.clear();
	meshAssets.resize(scene->mNumMeshes);
	// loop over meshes setting each one up
	for (int meshIndex = 0; meshIndex < scene->mNumMeshes; meshIndex++)
	{
		//meshes.emplace_back();
		DEBUG_PRINT("Name:" << scene->mMeshes[meshIndex]->mName.C_Str() << "Tex ID: " << scene->mMeshes[meshIndex]->mMaterialIndex);
		meshAssets[meshIndex].InitMesh(meshIndex, scene->mMeshes[meshIndex]);
	}

	return true;
}

const MeshAsset* StaticModelAsset::GetMeshAssets(uint& count)
{
	count = meshAssets.size();
	return &(meshAssets[0]);
}