#include "Component.h"

Component::Component(Actor* inOwner) : owner(inOwner)
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