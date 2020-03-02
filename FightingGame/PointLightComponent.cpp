#include "PointLightComponent.h"
#include "Master.h"

PointLightComponent::PointLightComponent(Actor* inOwner) : LightComponent(inOwner), position(glm::vec3(0)), atten()
{
	// Register Light
	registration = master->graphicsModule.lightMangager.RegisterPointLight(this);
}
PointLightComponent::~PointLightComponent()
{
	master->graphicsModule.lightMangager.UnregisterPointLight(registration);
}

void PointLightComponent::GetPointLightStruct(PointLight* outLight)
{
	outLight->base = base;
	outLight->atten = atten;
	outLight->position = glm::vec4(position,0);
}