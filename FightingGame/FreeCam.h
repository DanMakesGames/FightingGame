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
	float speed;
	float sensitivity;
	double oldMouseX, oldMouseY;


	static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	struct FreeCamInput
	{
		bool left, right, forwards, backwards, primFire, secFire;
		float camYaw, camPitch;
		FreeCamInput():
			left(0),
			right(0),
			forwards(0),
			backwards(0),
			primFire(0),
			secFire(0),
			camYaw(0.0f),
			camPitch(0.0f)
		{}
	};

	static FreeCamInput input;
};

