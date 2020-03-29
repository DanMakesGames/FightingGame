#pragma once
#include <vector>
#include <ctype.h>

// Set up GLM
#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"

// Set up GLEW
#define GLEW_STATIC
#pragma comment(lib, "glew32s.lib")
//#pragma comment(lib, "glew.lib")

#include "GL/glew.h"
#include <GLFW/glfw3.h>
#include "AssetManager.h"

#include "Core.h"
#include "GraphicsComponent.h"
#include "CameraComponent.h"
#include "LightManager.h"

class GraphicsComponent;
class PointLightComponent;

/*
Master of all 3d related operations.
Keeps references to all graphics objects, in order to facilitate a 
centralized render loop.

For future reference I think the most logcal way to organize things would be:
1. 3dAssets class
2. 3d asset renderers class
3. Graphical Components class

But im combining 3d asset renderers and graphical components because I'm lazy.
*/
class GraphicsModule
{
public:
	GLFWwindow* window;
	bool Initialize(AssetManager* inAssetManager);

	GraphicsModule();
	~GraphicsModule();

	// TODO this shouldn't be public. In the future all managers/modules will be under a central
	// control which someone can go ask for stuff from.
	AssetManager* assetManager;

	// loop over all graphicsComponents and render the scene.
	void RenderFrame(float deltaTime);

	std::list<GraphicsComponent*>::iterator RegisterComponent(GraphicsComponent* inComponent);
	void UnregisterComponent(const std::list<GraphicsComponent*>::iterator& it);

	std::list<CameraComponent*>::iterator RegisterCamera(CameraComponent* inComponent);
	void UnregisterCamera(const std::list<CameraComponent*>::iterator& regIndex);

	LightManager lightMangager;

	bool SetActiveCamera(CameraComponent* inCam);

	glm::vec2 GetWindowDim();

private:

	// GLFW stuff
	int windowX, windowY;

	// shader
	unsigned int fragmentShaderID;
	unsigned int vertexShaderID;
	unsigned int shaderProgramID;

	// returns shader ID
	GLuint InitializeShader(GLenum type, const char* filename);

	// returns program ID
	GLuint InitializeShaderProgram(GLuint fragID, GLuint vertID);

	// Refernces to all GraphicsComponents
	std::list<GraphicsComponent*> graphicsComponents;
	std::list<CameraComponent*> cameraComponents;
	CameraComponent* activeCamera;

};

