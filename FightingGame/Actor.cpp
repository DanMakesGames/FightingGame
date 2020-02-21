#include "Actor.h"

Actor::Actor() : position(0), rotation(glm::mat4(1))
{
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