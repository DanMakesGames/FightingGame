#pragma once
#include "Component.h"

#define ASPECT_DEFAULT 1.33f
#define FOV_DEFAULT 45.0f
#define NEAR_CLIP_DEFAULT 1.0f
#define FAR_CLIP_DEFAULT 1000.0f

class CameraComponent : public Component
{
public:
	CameraComponent(Actor* inOwner);
	~CameraComponent();

	void Tick(float deltaTime);

	void SetAspect(float inAspect);
	void SetFOV(float inFOV);
	void SetNearClip(float inNearClip);
	void SetFarClip(float inFarClip);

	void Update();

	glm::mat4 GetViewProjMat();
	
	void SetActive();

private:
	// registration index
	std::list<CameraComponent*>::iterator registration;

	// view projection matrix
	glm::mat4 viewProjMat;

	float aspect;
	// vertical fov in degrees
	float FOV;
	float nearClip;
	float farClip;
};

