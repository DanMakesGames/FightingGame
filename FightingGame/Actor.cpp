#include "Actor.h"

Actor::Actor() : position(0), rotation(glm::mat4(1))
{
	DefaultProperties();
}

bool Actor::DefaultProperties()
{
	return true;
}

bool Actor::Initialize()
{
	return true;
}

void Actor::Tick(float deltaTime)
{
}

glm::mat4 Actor::GetWorldMatrix()
{
	return glm::translate(position) * glm::mat4_cast(rotation) ;
}

void Actor::AttachComponent(Component* inComp)
{
	components.push_back(inComp);
}