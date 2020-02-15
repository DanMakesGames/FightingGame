#pragma once
#include "Core.h"
#include "Actor.h"

class Component
{
public:
	Component(Actor* inOwner);

	Actor* GetOwner();
	void SetOwner(Actor* inOwner);
	virtual void Initialize();

private:
	Actor* owner;
};

