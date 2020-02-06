#include "GraphicsModule.h"
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

bool GraphicsModule::Initialize()
{
	windowX = 800;
	windowY = 800;

	if (!glfwInit())
		return false;

	window = glfwCreateWindow(windowX, windowY, "FightingGame", NULL, NULL);
	glfwMakeContextCurrent(window);

	//init glew
	glewInit();
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

    // Initialize shader
    // Create the frage and vertex shaders.
    fragmentShaderID = InitializeShader(GL_FRAGMENT_SHADER, "fragShader.glsl");
    vertexShaderID = InitializeShader(GL_VERTEX_SHADER, "vertShader.glsl");

    shaderProgramID = InitializeShaderProgram(fragmentShaderID, vertexShaderID);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
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