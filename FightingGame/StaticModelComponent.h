#pragma once
#include "GraphicsComponent.h"
#include "AssetManager.h"
#include "Mesh.h"
#include "MaterialAsset.h"

class StaticModelComponent : public GraphicsComponent
{
public:
	using GraphicsComponent::GraphicsComponent;
	// used to load the right assets for this staticModel.
	// Set in the SetupProperties function of attached actor.

	// Set what model to load durring initialization.
	void SetModelSource(const string &source);

	// request assets and set up links to assets in meshes
	void Initialize();

	void Draw(const glm::mat4& modelMatrix, const glm::mat4& viewProjMatrix, uint shader);
	vector<std::string> materialFileNames;
private:

	std::string modelFileName;
	StaticModelAsset* modelAsset;
	vector<Mesh> meshes;


	vector<MaterialAsset*> materialAssets;
};

