#include "GraphicsModule.h"
#include "Mesh.h"
#include "StaticModel.h"
#include "Camera.h"
#include <iostream>
#include <fstream>
#include <string>

GraphicsModule::GraphicsModule()
{

}

GraphicsModule::~GraphicsModule()
{
    glDeleteShader(fragmentShaderID);
    glDeleteShader(vertexShaderID);
    glDeleteProgram(shaderProgramID);
}

bool GraphicsModule::Initialize(AssetManager* inAssetManager)
{
    assetManager = inAssetManager;
	windowX = 900;
	windowY = 900;

	if (!glfwInit())
		return false;

	window = glfwCreateWindow(windowX, windowY, "FightingGame", NULL, NULL);
	glfwMakeContextCurrent(window);
    
    GLenum res = glewInit();
    if (res != GLEW_OK)
    {
        fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
        return 1;
    }
	glEnable(GL_DEPTH_TEST);
    glClearColor(0., 0., 0., 1.);
	//glEnable(GL_CULL_FACE);

    // Initialize shader
    // Create the frage and vertex shaders.
    fragmentShaderID = InitializeShader(GL_FRAGMENT_SHADER, "fragmentShader.glsl");
    vertexShaderID = InitializeShader(GL_VERTEX_SHADER, "vertexShader.glsl");

    shaderProgramID = InitializeShaderProgram(fragmentShaderID, vertexShaderID);

    Mesh* testCube = new Mesh();
    testCube->MakeBox(glm::vec3(-1), glm::vec3(1));

    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile("Cloud_KH1.obj", aiProcess_Triangulate | aiProcess_GenSmoothNormals);
    //const aiScene* scene = importer.ReadFile("BoB.fbx", aiProcess_Triangulate | aiProcess_GenSmoothNormals);
    //const aiScene* scene = importer.ReadFile("giorno.obj", aiProcess_Triangulate | aiProcess_GenSmoothNormals);
    DEBUG_PRINT("Meshes: " << scene->mNumMeshes);

    StaticModel* testStaticModel = new StaticModel();
    testStaticModel->InitializeFromScene(scene);
    
    Camera cam;
    //cam.SetDistance(45.0f);
    cam.SetAspect(float(windowX) / float(windowY));

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        //glClear(GL_COLOR_BUFFER_BIT);
        glViewport(0, 0, windowX, windowY);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        cam.Update();
        
        //testCube->Draw(glm::mat4(1), cam.GetViewProjectMtx(), shaderProgramID);
        testStaticModel->Draw(glm::mat4(1), cam.GetViewProjectMtx(), shaderProgramID);

        glFinish();
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    delete testCube;
    delete testStaticModel;

    return 0;
}

GLuint GraphicsModule::InitializeShader(GLenum type,const char* filename)
{
    // open and read shader file.
    std::string fileData = "";
    std::ifstream fileStream(filename);

    if (!fileStream.good()) 
    {
        std::printf("error reading shader file.");
        return -1;
    }

    std::string line = "";
    while (getline(fileStream, line))
    {
        fileData += "\n" + line;
    }

    // create and compile new shader
    GLuint shaderID = glCreateShader(type);
    const char* fileDataCStr = fileData.c_str();
    glShaderSource(shaderID, 1, &fileDataCStr, NULL);
    glCompileShader(shaderID);

    GLint bIsCompiled = 0;
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &bIsCompiled);
    if (bIsCompiled == GL_FALSE)
    {
        printf("Cannot Compile Shader at %s: ", filename);
        // Print error message
        GLint maxLength = 0;
        glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &maxLength);
        std::vector<GLchar> errorLog(maxLength);
        glGetShaderInfoLog(shaderID, maxLength, &maxLength, &errorLog[0]);
        printf("GL ERRORS:\n%s\n", &errorLog[0]);

        glDeleteShader(shaderID);
        return -1;
    }

    return shaderID;
}

GLuint GraphicsModule::InitializeShaderProgram(GLuint fragID, GLuint vertID)
{
    GLuint programID = glCreateProgram();

    glAttachShader(programID, fragID);
    glAttachShader(programID, vertID);

    glLinkProgram(programID);

    GLint linked;
    glGetProgramiv(programID, GL_LINK_STATUS, &linked);
    if (linked) 
        glUseProgram(programID);
    else
    {
        printf("Error linking shader program.\n");
        return -1;
    }

    return programID;
}