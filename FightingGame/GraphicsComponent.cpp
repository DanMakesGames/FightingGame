#include "GraphicsComponent.h"

GraphicsComponent::GraphicsComponent(Actor* inOwner, GraphicsModule* inModule) : Component(inOwner), graphicsModule(inModule)
{

}

GraphicsModule* GraphicsComponent::GetGraphicsModule()
{
	return graphicsModule;
}