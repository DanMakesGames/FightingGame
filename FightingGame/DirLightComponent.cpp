#include "DirLightComponent.h"
#include "Master.h"
#include "Actor.h"

DirLightComponent::DirLightComponent(Actor* inOwner) : LightComponent(inOwner), direction(glm::vec3(0))
{
	registration = master->graphicsModule.lightMangager.RegisterDirLight(this);
}

DirLightComponent::~DirLightComponent()
{
	master->graphicsModule.lightMangager.UnregisterDirLight(registration);
}

void DirLightComponent::GetDirLightStruct(DirLight* outLight)
{
	outLight->base = base;
	outLight->dir = glm::normalize(GetOwner()->GetWorldMatrix() * glm::vec4(direction, 0));
}