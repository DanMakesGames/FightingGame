#include "CameraComponent.h"
#include "Master.h"
#include "Actor.h"

CameraComponent::CameraComponent(Actor* inOwner) : 
	Component(inOwner),
	aspect(ASPECT_DEFAULT),
	FOV(FOV_DEFAULT),
	nearClip(NEAR_CLIP_DEFAULT),
	farClip(FAR_CLIP_DEFAULT)
{
	registration = master->graphicsModule.RegisterCamera(this);
	Update();
}

CameraComponent::~CameraComponent()
{
	master->graphicsModule.UnregisterCamera(registration);
}

void CameraComponent::SetAspect(float inAspect)
{
	aspect = inAspect;
	Update();
}

void CameraComponent::SetFOV(float inFOV)
{
	FOV = inFOV;
	Update();
}

void CameraComponent::SetNearClip(float inNearClip)
{
	nearClip = inNearClip;
	Update();
}

void CameraComponent::SetFarClip(float inFarClip)
{
	farClip = inFarClip;
	Update();
}

glm::mat4 CameraComponent::GetViewProjMat()
{
	return viewProjMat;
}

void CameraComponent::Update()
{
	// view matrix generation
	Actor* owner = GetOwner();
	
	glm::mat4 offsetMat = glm::translate(localPosition);
	glm::mat4 ownerWorldMat = glm::translate(owner->position) * glm::mat4_cast(owner->rotation);
	glm::mat4 viewMat = glm::inverse(ownerWorldMat * offsetMat * glm::mat4_cast(localRotation));

	glm::mat4 projMat = glm::perspective(glm::radians(FOV), aspect, nearClip, farClip);

	viewProjMat = projMat * viewMat;
	
}

void CameraComponent::Tick(float deltaTime)
{
	Update();
}

void CameraComponent::SetActive()
{
	master->graphicsModule.SetActiveCamera(this);
}

void CameraComponent::Draw(uint shader)
{
	glUseProgram(shader);
	
	vec3 worldPosition = vec3(GetWorldMat() * vec4(0, 0, 0, 1));
	
	glUniform3fv(glGetUniformLocation(shader, "eyePos"), 1, (float*)&worldPosition);

	glUseProgram(0);
}