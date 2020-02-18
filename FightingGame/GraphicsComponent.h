#pragma once
#include "Component.h"
#include "GraphicsModule.h"

/*
A renderable component. references to all of these components are
stored in the GraphicsModule, and looped over to render.
*/
class GraphicsComponent : public Component
{
public:
	GraphicsComponent(Actor* inOwner, GraphicsModule* inModule);

	virtual void Draw(const glm::mat4& modelMatrix, const glm::mat4& viewProjMatrix, uint shader)=0;

	GraphicsModule* GetGraphicsModule();

private:

	GraphicsModule* graphicsModule;
};

