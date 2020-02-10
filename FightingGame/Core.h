#pragma once
#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"

// Set up GLEW
#define GLEW_STATIC
#pragma comment(lib, "glew32s.lib")
//#pragma comment(lib, "glew.lib")

#include "GL/glew.h"

#include <GLFW/glfw3.h>

#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/Importer.hpp>
#include <assimp/types.h>

typedef unsigned int uint;

#include <iostream>

#define DEBUG 1
#define DEBUG_PRINT(a) if(DEBUG) std::cout<< a <<std::endl;

// how many indices per polygon. Should be 3 for triangles.
#define POLYGON_INDEX_COUNT 3