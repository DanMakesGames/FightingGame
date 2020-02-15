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
master of all 3d related operations.
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
	
};

