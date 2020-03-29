#include "LightManager.h"

LightManager::~LightManager()
{
    DEBUG_PRINT("Destroy Light Manager");
    glDeleteBuffers(1, &lightBlock);
}

void LightManager::Initialize(GLuint shader)
{
    // establish the light UBO
    const uint lightUBOSize = 16 + (100 * 64);
    GLuint lightBlockLoc = glGetUniformBlockIndex(shader, "LightBlock");
    glUniformBlockBinding(shader, lightBlockLoc, 0);
    char buf[30];
    int len = 0;
    int size = 0;
    GLenum type;
    //glGetActiveUniform(shader,lightBlockLoc,20,&len,&size,&type,buf);
    glGetActiveUniformBlockiv(shader, lightBlock, GL_UNIFORM_BLOCK_DATA_SIZE, &len);
    //DEBUG_PRINT(buf << ": " << size);
    DEBUG_PRINT("frag block " << len);
    DEBUG_PRINT("my block " << sizeof(LightBlock));

    glUseProgram(shader);
    glGenBuffers(1, &lightBlock);

    glBindBuffer(GL_UNIFORM_BUFFER, lightBlock);
    glBufferData(GL_UNIFORM_BUFFER, len, NULL, GL_DYNAMIC_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    glBindBufferRange(GL_UNIFORM_BUFFER, 0, lightBlock, 0, 16);

    glUseProgram(0);
    CurrentShader = shader;
    //UpdateLightBuffer(shader);
}

void LightManager::UpdateLightBuffer(const glm::mat4& viewProjMatrix, uint shader)
{
    // loop over pointlights and build new list

    LightBlock lightBlockStruct;
    int pointLightIndex = 0;
    for (auto it = pointLights.begin(); it != pointLights.end(); it++)
    {
        (*it)->GetPointLightStruct(&(lightBlockStruct.pointLights[pointLightIndex]));
        lightBlockStruct.pointLights[pointLightIndex].position = viewProjMatrix * lightBlockStruct.pointLights[pointLightIndex].position;
        pointLightIndex++;
    }
    int dirLightIndex = 0;
    for (auto it = dirLights.begin(); it != dirLights.end(); it++)
    {
        (*it)->GetDirLightStruct(&(lightBlockStruct.dirLights[dirLightIndex]));
        dirLightIndex++;
    }

    lightBlockStruct.numberPointLights = pointLightIndex;
    lightBlockStruct.numberDirLights = dirLightIndex;

    glBindBuffer(GL_UNIFORM_BUFFER, lightBlock);
    glBufferSubData(GL_UNIFORM_BUFFER, 0,sizeof(lightBlockStruct), &lightBlockStruct);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

std::list<PointLightComponent*>::iterator LightManager::RegisterPointLight(PointLightComponent* inLight)
{
    pointLights.push_front(inLight);
    return pointLights.begin();
}

void LightManager::UnregisterPointLight(const std::list<PointLightComponent*>::iterator& it)
{
    pointLights.erase(it);
}

std::list<DirLightComponent*>::iterator LightManager::RegisterDirLight(DirLightComponent* inLight)
{
    dirLights.push_front(inLight);
    //UpdateLightBuffer(CurrentShader);
    return dirLights.begin();
}

void LightManager::UnregisterDirLight(const std::list<DirLightComponent*>::iterator& it)
{
    dirLights.erase(it);
}