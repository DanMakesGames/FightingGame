#pragma once
#include "Object.h"
#include "Core.h"
#include "Component.h"


/*
Conceptually equivalent to the Unreal Actor.
Anything that exists in the pyhsical game world is an actor.
Any graphic must be attached to an actor.
*/
class Actor : public Object
{
public:
	// this is where components are set up and defined, as well as any other default properties. 
	virtual bool SetupProperties();
	virtual bool Initialize();
	virtual void Tick(float deltaTime);
	
private:

	// Actor position properties
	glm::vec3 position;
	glm::quat rotation;

	std::vector<class Component*> components;
};

