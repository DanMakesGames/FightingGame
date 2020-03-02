#pragma once
#include "Core.h"
#include "Component.h"

struct LightBase
{
	glm::vec4 color;
	float ambientIntensity;
	float diffuseIntensity;
	float padding[2];

	LightBase():color(glm::vec4(1)),ambientIntensity(1),diffuseIntensity(1)
	{
	}
};

class LightComponent : public Component
{
public:
	LightComponent(Actor*);
	
	LightBase base;
};

