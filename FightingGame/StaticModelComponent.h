#pragma once
#include "GraphicsComponent.h"
class StaticModelComponent : public GraphicsComponent
{
public:

	// used to load the right assets for this staticModel.
	// Set in the SetupProperties function of attached actor.
	std::string modelFileName;
	vector<std::string> textureFileNames;

private:
	handle staticModel;
	vector<handle> textures;
};

