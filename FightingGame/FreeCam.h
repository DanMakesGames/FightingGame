#pragma once
#include "Actor.h"

// Simple flying camera for testing and debug.
class FreeCam : public Actor
{
public:
	FreeCam();
	~FreeCam();
	bool DefaultProperties();
	bool Initialize();
	void Tick(float deltaTime);

private:
	class CameraComponent* camera;
};

