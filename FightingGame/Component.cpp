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

glm::mat4 Component::GetWorldMat()
{
	Actor* owner = GetOwner();

	glm::mat4 offsetMat = glm::translate(localPosition);
	glm::mat4 ownerWorldMat = glm::translate(owner->position) * glm::mat4_cast(owner->rotation);
	glm::mat4 worldMat = ownerWorldMat * offsetMat * glm::mat4_cast(localRotation);

	return worldMat;
}