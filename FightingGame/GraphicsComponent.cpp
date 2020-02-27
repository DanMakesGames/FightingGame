#include "GraphicsComponent.h"
#include "Master.h"

GraphicsComponent::GraphicsComponent(Actor* inOwner) : Component(inOwner)
{
	graphicsModule = &(master->graphicsModule);

	// TODO: register self with graphics module.
	registration = graphicsModule->RegisterComponent(this);
}

GraphicsComponent::~GraphicsComponent()
{
	// remove self from GraphicsModule registry
	graphicsModule->UnregisterComponent(registration);
}

GraphicsModule* GraphicsComponent::GetGraphicsModule()
{
	return graphicsModule;
}