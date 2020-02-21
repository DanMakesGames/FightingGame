#pragma once
#include "Core.h"
#include "Actor.h"

class Component
{
public:
	Component(class Actor* inOwner);

	Actor* GetOwner();
	void SetOwner(class Actor* inOwner);
	virtual void Initialize();
	glm::vec3 localPosition;
	glm::quat localRotation;

private:
	class Actor* owner;

};

