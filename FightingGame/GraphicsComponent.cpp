#include "GraphicsComponent.h"

GraphicsComponent::GraphicsComponent(Actor* inOwner, GraphicsModule* inModule) : Component(inOwner), graphicsModule(inModule)
{
	// TODO: register self with graphics module.
}

GraphicsModule* GraphicsComponent::GetGraphicsModule()
{
	return graphicsModule;
}