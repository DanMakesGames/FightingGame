#include "StaticModel.h"

StaticModel::StaticModel() : worldMatrix(glm::mat4(1)), worldPosition(glm::vec3(0)), localMatrix(glm::mat4(1))
{
}
StaticModel::~StaticModel()
{

}

void StaticModel::Draw(const glm::mat4& modelMatrix, const glm::mat4& viewProjMatrix, uint shader)
{
	// loop over meshes and render
	for (int meshIndex = 0; meshIndex < meshes.size(); meshIndex++)
	{
		meshes[meshIndex].Draw(modelMatrix, viewProjMatrix, shader);
	}
}

bool StaticModel::LoadFromFile(std::string fileName)
{

}

bool StaticModel::InitializeFromScene(const aiScene* scene)
{

	if (!scene->HasMeshes())
		return true;
	meshes.clear();
	meshes.resize(scene->mNumMeshes);
	// loop over meshes setting each one up
	for (int meshIndex = 0; meshIndex < scene->mNumMeshes; meshIndex++)
	{
		//meshes.emplace_back();
		DEBUG_PRINT("Name:"<< scene->mMeshes[meshIndex]->mName.C_Str()<<"Tex ID: "<< scene->mMeshes[meshIndex]->mMaterialIndex);
		meshes[meshIndex].InitMesh(meshIndex, scene->mMeshes[meshIndex]);
	}
}