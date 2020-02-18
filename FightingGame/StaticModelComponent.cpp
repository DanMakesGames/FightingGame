#include "StaticModelComponent.h"

void StaticModelComponent::Initialize()
{
	GraphicsModule* graphicsModule = GetGraphicsModule();

	// Request the static model asset.
	modelAsset = (StaticModelAsset*)graphicsModule->assetManager->LoadAsset(modelFileName, Asset::EAssetType::AT_STATIC_MODEL);
	
	// loop initializing meshes
	uint meshCount = 0;
	
	const MeshAsset* meshAssets = modelAsset->GetMeshAssets(meshCount);
	DEBUG_PRINT("Init Component mesh count: " << meshCount);

	meshes.resize(meshCount);

	for (int meshIndex = 0; meshIndex < meshCount; meshIndex++)
	{
		DEBUG_PRINT("init mesh "<<meshIndex);
		meshes[meshIndex].Initialize(&(meshAssets[meshIndex]));
	}
}

void StaticModelComponent::Draw(const glm::mat4& modelMatrix, const glm::mat4& viewProjMatrix, uint shader)
{
	// loop over meshes, drawing them.

	// important that you need to take into account the attached actor's position and rotation.
}

void StaticModelComponent::SetModelSource(const string &source)
{
	modelFileName = source;
}

