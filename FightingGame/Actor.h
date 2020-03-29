#pragma once

#include "Core.h"
#include "Object.h"
//#include "Component.h"

class Component;

/*
Conceptually equivalent to the Unreal Actor.
Anything that exists in the pyhsical game world is an actor.
Any graphic must be attached to an actor.
*/
class Actor : public Object
{
public:
	Actor();
	// this is where components are set up and defined, as well as any other default properties. 
	virtual bool DefaultProperties();
	virtual bool Initialize();
	virtual void Tick(float deltaTime);
	// Actor position properties
	glm::vec3 position;
	glm::quat rotation;

	glm::mat4 GetWorldMatrix();
	void AttachComponent(Component* inComp);

private:

	std::vector<Component*> components;
};

