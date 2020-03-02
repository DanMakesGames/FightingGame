#pragma once
#include "Core.h"
#include "LightCore.h"
#include "PointLightComponent.h"

struct LightBlock
{
	int numberPointLights;
	float padding[3];
	PointLight pointLights[MAX_POINT_LIGHT];

};

/*
The graphics module was getting to fucking big. 
All lights and properties are handled her.
*/
class LightManager
{
public:
	~LightManager();
	void Initialize(GLuint shader);

	void UpdateLightBuffer(const glm::mat4& viewProjMatrix, uint shader);

	std::list<PointLightComponent*>::iterator RegisterPointLight(PointLightComponent* inLight);

	void UnregisterPointLight(const std::list<PointLightComponent*>::iterator& it);

private:
	std::list<PointLightComponent*> pointLights;

	GLuint lightBlock;
	GLuint CurrentShader;


	// not neccessry when using Uniform Buffers.
	struct PointLightLocation
	{
		GLuint color;
		GLuint ambientIntensity;
		GLuint diffuseIntensity;
		GLuint position;
		struct
		{
			GLuint constant;
			GLuint linear;
			GLuint exp;
		} Atten;
	};

	std::vector<PointLightLocation> pointLightShaderLocs;
};

