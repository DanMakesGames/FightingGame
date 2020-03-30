#include "FreeCam.h"
#include "CameraComponent.h"
#include "Master.h"

FreeCam::FreeCamInput FreeCam::input;

FreeCam::FreeCam() : speed(3.0f), sensitivity(0.001f)
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
	glfwSetKeyCallback(master->graphicsModule.GetWindow(), &(this->keyCallback));
	return true;
}

bool FreeCam::Initialize()
{

	return true;
}

void FreeCam::Tick(float deltaTime)
{
	// handle some input and go nuts go crazy
	GLFWwindow* window = master->graphicsModule.GetWindow();

	glm::vec3 heading = glm::mat4_cast(rotation) * glm::vec4(0, 0, 1, 0);
	glm::vec3 orthoHeading = glm::mat4_cast(rotation) * glm::vec4(1, 0, 0, 0);
	heading = glm::normalize(heading);

	if (input.forwards)
	{
		position += heading * -speed * deltaTime;
	}
	if (input.backwards)
	{
		position += heading * speed * deltaTime;
	}
	if (input.right)
	{
		position += orthoHeading * speed * deltaTime;
	}
	if (input.left)
	{
		position += orthoHeading * -speed * deltaTime;
	}

	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);
	double mouseDeltaX = xpos - oldMouseX;
	double mouseDeltaY = ypos - oldMouseY;
	oldMouseX = xpos;
	oldMouseY = ypos;
	input.camYaw += -1.0f * mouseDeltaX * sensitivity;
	input.camPitch +=-1.0f * mouseDeltaY * sensitivity;
	glm::vec3 yawAxis(0, 1, 0);

	glm::quat yaw = glm::rotate(float(input.camYaw), yawAxis);
	glm::quat pitch = glm::rotate(float(input.camPitch), vec3(1,0,0));

	rotation = yaw * pitch;
}

void FreeCam::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	switch (key)
	{
	case GLFW_KEY_W:
		if (action == GLFW_PRESS)
			input.forwards = true;
		else if (action == GLFW_RELEASE)
			input.forwards = false;
		break;
	case GLFW_KEY_S:
		if (action == GLFW_PRESS)
			input.backwards = true;
		else if (action == GLFW_RELEASE)
			input.backwards = false;
		break;
	case GLFW_KEY_D:
		if (action == GLFW_PRESS)
			input.right = true;
		else if (action == GLFW_RELEASE)
			input.right = false;
		break;
	case GLFW_KEY_A:
		if (action == GLFW_PRESS)
			input.left = true;
		else if (action == GLFW_RELEASE)
			input.left = false;
		break;
	}
}