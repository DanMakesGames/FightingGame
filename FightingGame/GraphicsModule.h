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
#include <Magick++.h>

#include "AssetManager.h"

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
	bool Initialize(AssetManager* inAssetManager);

	GraphicsModule();
	~GraphicsModule();

	// load assets from 

private:

	// GLFW stuff
	int windowX, windowY;
	GLFWwindow* window;

	// shader
	unsigned int fragmentShaderID;
	unsigned int vertexShaderID;
	unsigned int shaderProgramID;

	// returns shader ID
	GLuint InitializeShader(GLenum type, const char* filename);

	// returns program ID
	GLuint InitializeShaderProgram(GLuint fragID, GLuint vertID);

	// pool of loaded assets.
	AssetManager* assetManager;

	// Refernces to all 
	
};

