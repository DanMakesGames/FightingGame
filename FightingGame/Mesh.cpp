#include "Mesh.h"

Mesh::Mesh()
{
	// set up index and vertex buffers
	glGenBuffers(1, &vertexBuffer);
	glGenBuffers(1, &indexBuffer);
}

Mesh::~Mesh()
{
	glDeleteBuffers(1, &vertexBuffer);
	glDeleteBuffers(1, &indexBuffer);
}

void Mesh::Draw(const glm::mat4& modelMatrix, const glm::mat4& viewProjMatrix, uint shader)
{
	// set shader program to use
	glUseProgram(shader);

	//glUniformMatrix4fv(glGetUniformLocation(shader,));
}