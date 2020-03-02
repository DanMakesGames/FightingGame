#pragma once
#include "Core.h"
#include "LightComponent.h"

struct Attenuation
{
	float constant;
	float linear;
	float exp;
	float padding;
	Attenuation():constant(0),linear(0),exp(1),padding(0)
	{
	}
};

struct PointLight
{
	LightBase base;
	glm::vec4 position;
	Attenuation atten;

	PointLight():position(glm::vec4(0)), base()
	{
	}
};

class PointLightComponent : public LightComponent
{
public:
	PointLightComponent(Actor* inOwner);
	~PointLightComponent();
	
	glm::vec3 position;
	Attenuation atten;
	void GetPointLightStruct(PointLight* outLight);

private:
	std::list<PointLightComponent*>::iterator registration;
};

