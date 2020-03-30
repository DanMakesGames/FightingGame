#pragma once
#include "Core.h"
#include "Object.h"
#include "Actor.h"

class Actor;

class Component : public Object
{
public:
	Component(Actor* inOwner);

	Actor* GetOwner();
	void SetOwner(Actor* inOwner);
	virtual void Initialize();
	virtual void Tick(float deltaTime);
	glm::vec3 localPosition;
	glm::quat localRotation;
	glm::mat4 GetWorldMat();
private:
	Actor* owner;

};

