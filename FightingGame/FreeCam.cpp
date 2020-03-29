#include "FreeCam.h"
#include "CameraComponent.h"
#include "Master.h"

FreeCam::FreeCam()
{
	DefaultProperties();
}

FreeCam::~FreeCam()
{
	delete camera;
}

bool FreeCam::DefaultProperties()
{
	camera = new CameraComponent(this);
	glm::vec2 windowDim = master->graphicsModule.GetWindowDim();
	camera->SetAspect(windowDim.x / windowDim.y);
	AttachComponent(camera);
	camera->SetActive();

	return true;
}

bool FreeCam::Initialize()
{
	return true;
}

void FreeCam::Tick(float deltaTime)
{
	// handle some input and go nuts go crazy
}