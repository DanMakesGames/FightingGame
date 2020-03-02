#pragma once
#include "LightComponent.h"

struct DirLight
{
	LightBase base;
	glm::vec4 dir;
	DirLight() : dir(glm::vec4(0)), base()
	{
	}
};

class DirLightComponent : public LightComponent
{
public:
	DirLightComponent(Actor* inOwner);
	~DirLightComponent();
	
	glm::vec3 direction;
	void GetDirLightStruct(DirLight* outLight);

private:
	std::list<DirLightComponent*>::iterator registration;
};

