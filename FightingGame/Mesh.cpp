#include "Mesh.h"

Mesh::Mesh() : meshAsset(-1)
{
	// set up index and vertex buffers
	glGenBuffers(1, &vertexBuffer);
	glGenBuffers(1, &indexBuffer);
	Count = 0;
}

Mesh::~Mesh()
{
	glDeleteBuffers(1, &vertexBuffer);
	glDeleteBuffers(1, &indexBuffer);
}

void Mesh::Draw(const glm::mat4& meshMatrix, const glm::mat4& viewProjMatrix, uint shader)
{
	// set shader program to use
	glUseProgram(shader);

	// set the uniforms
	// model oriegntation, for example controlled by the actor this is attached to's position.
	glUniformMatrix4fv(glGetUniformLocation(shader,"meshMatrix"), 1, false,(float*)&meshMatrix);

	// set up view projection martrix for camera control.
	glUniformMatrix4fv(glGetUniformLocation(shader, "projMatrix"), 1, false, (float*)&viewProjMatrix);

	// bind the vertex and index buffers
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);

	// structure of the model vertex attributes
	uint positionLocation = 0;
	uint normalLocation = 1;

	// set position attribute in the GL_ARRAY_BUFFER, which is the buffer being used for vertex attributes
	glEnableVertexAttribArray(positionLocation);
	glVertexAttribPointer(positionLocation, 3, GL_FLOAT, GL_FALSE, sizeof(ModelVertex), 0);

	// ditto for normal vertex attribute
	glEnableVertexAttribArray(normalLocation);
	glVertexAttribPointer(normalLocation, 3, GL_FLOAT, GL_FALSE, sizeof(ModelVertex), (void*)12);

	//glDrawArrays(GL_TRIANGLES, 0, Count);
	glDrawElements(GL_TRIANGLES, Count, GL_UNSIGNED_INT, 0);

	// clean up state aka debind the buffers and the program.
	glDisableVertexAttribArray(positionLocation);
	glDisableVertexAttribArray(normalLocation);

	// unbind buffers
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glUseProgram(0);
}

void Mesh::SetBuffers(const std::vector<ModelVertex>& vertexData, const std::vector<uint>& indexData)
{
	Count = (int)indexData.size();
	printf("count: %d\n",Count);

	// store vertex data in buffer
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertexData.size() * sizeof(ModelVertex),&vertexData[0],GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexData.size() * sizeof(uint), &indexData[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}

void Mesh::MakeBox(const glm::vec3& boxMin, const glm::vec3& boxMax) {
	// Specify vertices
	std::vector<ModelVertex> vtx = {
		// Front
		{{boxMin.x,boxMin.y,boxMax.z},	{0,0,1}},
		{{boxMax.x,boxMin.y,boxMax.z},	{0,0,1}},
		{{boxMax.x,boxMax.y,boxMax.z},	{0,0,1}},
		{{boxMin.x,boxMax.y,boxMax.z},	{0,0,1}},

		// Back
		{{boxMax.x,boxMin.y,boxMin.z},	{0,0,-1}},
		{{boxMin.x,boxMin.y,boxMin.z},	{0,0,-1}},
		{{boxMin.x,boxMax.y,boxMin.z},	{0,0,-1}},
		{{boxMax.x,boxMax.y,boxMin.z},	{0,0,-1}},

		// Top
		{{boxMin.x,boxMax.y,boxMax.z},	{0,1,0}},
		{{boxMax.x,boxMax.y,boxMax.z},	{0,1,0}},
		{{boxMax.x,boxMax.y,boxMin.z},	{0,1,0}},
		{{boxMin.x,boxMax.y,boxMin.z},	{0,1,0}},

		// Bottom
		{{boxMin.x,boxMin.y,boxMin.z},	{0,-1,0}},
		{{boxMax.x,boxMin.y,boxMin.z},	{0,-1,0}},
		{{boxMax.x,boxMin.y,boxMax.z},	{0,-1,0}},
		{{boxMin.x,boxMin.y,boxMax.z},	{0,-1,0}},

		// Left
		{{boxMin.x,boxMin.y,boxMin.z},	{-1,0,0}},
		{{boxMin.x,boxMin.y,boxMax.z},	{-1,0,0}},
		{{boxMin.x,boxMax.y,boxMax.z},	{-1,0,0}},
		{{boxMin.x,boxMax.y,boxMin.z},	{-1,0,0}},

		// Right
		{{boxMax.x,boxMin.y,boxMax.z},	{1,0,0}},
		{{boxMax.x,boxMin.y,boxMin.z},	{1,0,0}},
		{{boxMax.x,boxMax.y,boxMin.z},	{1,0,0}},
		{{boxMax.x,boxMax.y,boxMax.z},	{1,0,0}},
	};

	// Specify indices
	std::vector<uint> idx = {
		0,1,2,		0,2,3,			// Front
		4,5,6,		4,6,7,			// Back
		8,9,10,		8,10,11,		// Top
		12,13,14,	12,14,15,		// Bottom
		16,17,18,	16,18,19,		// Left
		20,21,22,	20,22,23,		// Right
	};

	// Create vertex & index buffers
	SetBuffers(vtx, idx);
}