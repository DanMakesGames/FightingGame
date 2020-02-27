#pragma once
#include "Core.h"
#include "Component.h"
#include "GraphicsModule.h"

class GraphicsModule;

/*
A renderable component. references to all of these components are
stored in the GraphicsModule, and looped over to render.
*/
class GraphicsComponent : public Component
{
public:
	GraphicsComponent(Actor* inOwner);
	~GraphicsComponent();
	virtual void Draw(const glm::mat4& modelMatrix, const glm::mat4& viewProjMatrix, uint shader)=0;

	GraphicsModule* GetGraphicsModule();

private:

	// used to access location in GraphicsModule register for removal at end of life
	std::list<GraphicsComponent*>::iterator registration;
	GraphicsModule* graphicsModule;
};

