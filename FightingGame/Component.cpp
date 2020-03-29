#include "Component.h"
#include "Actor.h"

Component::Component(Actor* inOwner) : owner(inOwner), localRotation(glm::mat4(1)), localPosition(0)
{
}

Actor* Component::GetOwner()
{
	return owner;
}

void Component::SetOwner(Actor* inOwner)
{
	owner = inOwner;
}

void Component::Initialize() {}

void Component::Tick(float deltaTime) {}