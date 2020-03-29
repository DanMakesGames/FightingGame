#include "Mesh.h"

Mesh::Mesh() : meshAsset(nullptr), texAsset(nullptr)
{
	// set up index and vertex buffers
	glGenBuffers(1, &vertexBuffer);
	glGenBuffers(1, &indexBuffer);
	glGenTextures(1, &texBuffer);
	Count = 0;
}

Mesh::~Mesh()
{
	glDeleteBuffers(1, &vertexBuffer);
	glDeleteBuffers(1, &indexBuffer);
	glDeleteTextures(1, &texBuffer);
}

bool Mesh::Initialize(const MeshAsset* inMeshAsset)
{
	meshAsset = inMeshAsset;
	meshData = inMeshAsset->GetMeshDataPointers();

	SetPrimativeBuffers(meshData.vertices, meshData.verticesCount, meshData.indices, meshData.indicesCount);

	return true;
}

bool Mesh::Initialize(const MeshAsset* inMeshAsset, const TextureAsset* inTexAsset)
{
	meshAsset = inMeshAsset;
	meshData = inMeshAsset->GetMeshDataPointers();

	SetPrimativeBuffers(meshData.vertices, meshData.verticesCount, meshData.indices, meshData.indicesCount);

	if (inTexAsset != nullptr)
	{
		texAsset = inTexAsset;
		texData = texAsset->GetTextureData();
		SetTextureBuffers(texData.data, texData.width, texData.height);
	}

	return true;
}

bool Mesh::Initialize(const MeshAsset* inMeshAsset, const MaterialAsset* inMatAsset)
{
	meshAsset = inMeshAsset;
	meshData = inMeshAsset->GetMeshDataPointers();

	SetPrimativeBuffers(meshData.vertices, meshData.verticesCount, meshData.indices, meshData.indicesCount);

	matAsset = inMatAsset;

	if (inMatAsset != nullptr)
	{
		MaterialAsset::MaterialData matData = inMatAsset->GetData();
		if (matData.texture != nullptr)
		{
			texAsset = matData.texture;
			texData = texAsset->GetTextureData();
			SetTextureBuffers(texData.data, texData.width, texData.height);
		}
	}
	
	return true;
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

	glUniform1i(glGetUniformLocation(shader, "texSampler"), 0);

	MaterialAsset::MaterialData finalMatData;

	// material
	if (matAsset != nullptr)
	{
		finalMatData = matAsset->GetData();
	}

	glUniform3fv(glGetUniformLocation(shader, "material.ambient"), 1, (float*)&finalMatData.ambient);
	glUniform3fv(glGetUniformLocation(shader, "material.diffuse"), 1, (float*)&finalMatData.diffuse);
	glUniform3fv(glGetUniformLocation(shader, "material.specular"), 1, (float*)&finalMatData.specular);
	glUniform1f(glGetUniformLocation(shader, "material.shininess"), finalMatData.shininess);

	// bind the vertex and index buffers
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);

	// structure of the model vertex attributes
	uint positionLocation = 0;
	uint normalLocation = 1;
	uint UVCoordLocation = 2;

	// set position attribute in the GL_ARRAY_BUFFER, which is the buffer being used for vertex attributes
	glEnableVertexAttribArray(positionLocation);
	// the stride is the size to hop between elements of the generic array. It is the size of each vert.
	// the final property is a pointer to the first element. Normal is after position, so normal starts 
	// at 3 * 4 bytes = 12 bytes into the array.
	glVertexAttribPointer(positionLocation, 3, GL_FLOAT, GL_FALSE, sizeof(ModelVertex), 0);

	// ditto for normal vertex attribute
	glEnableVertexAttribArray(normalLocation);
	glVertexAttribPointer(normalLocation, 3, GL_FLOAT, GL_FALSE, sizeof(ModelVertex), (void*)12);

	glEnableVertexAttribArray(UVCoordLocation);
	glVertexAttribPointer(UVCoordLocation, 2, GL_FLOAT, GL_FALSE, sizeof(ModelVertex), (void*)24);

	// bind texture if one exists
	if (texAsset != nullptr)
	{
		//SetTextureBuffers(texData.data,texData.width, texData.height);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texBuffer);
		glUniform1i(glGetUniformLocation(shader, "bIsTextured"), 1);
	}
	else
	{
		glUniform1i(glGetUniformLocation(shader, "bIsTextured"), 0);
	}

	glDrawElements(GL_TRIANGLES, Count, GL_UNSIGNED_INT, 0);

	// clean up state aka debind the buffers and the program.
	glDisableVertexAttribArray(positionLocation);
	glDisableVertexAttribArray(normalLocation);

	// unbind buffers
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);

	glUseProgram(0);
}

void Mesh::SetPrimativeBuffers(const ModelVertex* vertexData, const uint& vertexDataCount, const uint* indexData, const uint& indexDataCount)
{
	Count = indexDataCount;

	// store vertex data in buffer
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertexDataCount * sizeof(ModelVertex), vertexData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexDataCount * sizeof(uint), indexData, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Mesh::SetPrimativeBuffers(const std::vector<ModelVertex>& vertexData, const std::vector<uint>& indexData)
{
	SetPrimativeBuffers(&vertexData[0], vertexData.size(), &indexData[0], indexData.size());
}

void Mesh::SetTextureBuffers(const void* texPixelData, const uint& texWidth, const uint& texHeight)
{
	glBindTexture(GL_TEXTURE_2D, texBuffer);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texWidth, texHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, texPixelData);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);
	DEBUG_PRINT("texbuff: "<< texBuffer);

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
	SetPrimativeBuffers(vtx, idx);
}