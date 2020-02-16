#pragma once
#include "GraphicsComponent.h"
#include "Mesh.h"
class StaticModelComponent : public GraphicsComponent
{
public:

	// used to load the right assets for this staticModel.
	// Set in the SetupProperties function of attached actor.


private:
	vector<Mesh> meshes;
	std::string modelFileName;
	vector<std::string> textureFileNames;
};

