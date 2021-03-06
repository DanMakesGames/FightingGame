#pragma once
#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtc/quaternion.hpp"
#include "glm/gtx/euler_angles.hpp"
#include "glm/gtx/string_cast.hpp"

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

#define ASSIMP_STATIC_MODEL_IMPORT_SETTINGS aiProcess_Triangulate | aiProcess_GenSmoothNormals

typedef unsigned int uint;

// a handle type. Id used to access something.
// Value of -1 means uninitialized.
typedef unsigned int handle;

#include <iostream>
#include <string>
#include <vector>
#include <list>

#define DEBUG 1
#define DEBUG_PRINT(a) if(DEBUG) std::cout<< a <<std::endl;

// how many indices per polygon. Should be 3 for triangles.
#define POLYGON_INDEX_COUNT 3

using namespace std;
using namespace glm;