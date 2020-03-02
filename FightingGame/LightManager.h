#pragma once
#include "Core.h"
#include "LightCore.h"
#include "PointLightComponent.h"
#include "DirLightComponent.h"

struct LightBlock
{
	int numberPointLights;
	int numberDirLights;
	float padding[2];
	PointLight pointLights[MAX_POINT_LIGHT];
	DirLight dirLights[MAX_DIR_LIGHT];

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

	std::list<DirLightComponent*>::iterator RegisterDirLight(DirLightComponent* inLight);
	void UnregisterDirLight(const std::list<DirLightComponent*>::iterator& it);

private:
	std::list<PointLightComponent*> pointLights;
	std::list<DirLightComponent*> dirLights;

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

