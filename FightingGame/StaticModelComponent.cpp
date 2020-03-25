#include "StaticModelComponent.h"
#include "Actor.h"
#include "Master.h"

void StaticModelComponent::Initialize()
{
	GraphicsModule* graphicsModule = GetGraphicsModule();

	bool bHasTex = false;

	// load textures
	if (materialFileNames.size() != 0)
	{
		bHasTex = true;
		for (int matIndex = 0; matIndex < materialFileNames.size(); matIndex++)
		{
			materialAssets.emplace_back((TextureAsset*)master->assetManager.LoadAsset(materialFileNames[matIndex], Asset::EAssetType::AT_MATERIAL));
		}
	}

	// Request the static model asset.
	modelAsset = (StaticModelAsset*)graphicsModule->assetManager->LoadAsset(modelFileName, Asset::EAssetType::AT_STATIC_MODEL);
	
	// loop initializing meshes
	uint meshCount = 0;
	
	const MeshAsset* meshAssets = modelAsset->GetMeshAssets(meshCount);
	DEBUG_PRINT("Init Component mesh count: " << meshCount);

	meshes.resize(meshCount);
	// create meshes based on model asset.
	for (int meshIndex = 0; meshIndex < meshCount; meshIndex++)
	{
		DEBUG_PRINT("init mesh " << meshIndex);

		// look to see if this mesh needs a texture.
		if (bHasTex && meshAssets[meshIndex].materialIndex < materialAssets.size())
		{
			uint matIndex = meshAssets[meshIndex].materialIndex;	
			meshes[meshIndex].Initialize(&(meshAssets[meshIndex]), materialAssets[matIndex]);
		}
		// no texture initialization
		else
		{
			meshes[meshIndex].Initialize(&(meshAssets[meshIndex]));
		}
	}
}

void StaticModelComponent::Draw(const glm::mat4& modelMatrix, const glm::mat4& viewProjMatrix, uint shader)
{
	// loop over meshes, drawing them.

	// important that you need to take into account the attached actor's position and rotation.
	Actor* owner = GetOwner();
	glm::mat4 offsetMatrix = glm::translate(localPosition);
	glm::mat4 actorWorldMatrix = glm::translate(GetOwner()->position) * glm::mat4_cast(owner->rotation);
	glm::mat4 worldMatrix = actorWorldMatrix * offsetMatrix * glm::mat4_cast(localRotation);

	for (int meshIndex = 0; meshIndex < meshes.size(); meshIndex++)
	{
		meshes[meshIndex].Draw(worldMatrix, viewProjMatrix, shader);
	}
}

void StaticModelComponent::SetModelSource(const string &source)
{
	modelFileName = source;
}

