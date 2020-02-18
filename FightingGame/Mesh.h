#pragma once
#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"
#include "Core.h"
#include "MeshAsset.h"
#include <vector>

/*
While there will be subclasses of this class (Skin...) all potential
properties of mesh will be loaded here (for example wi) 
*/


class Mesh
{
public:
	Mesh();
	~Mesh();

	void Draw(const glm::mat4 &modelMatrix, const glm::mat4 &viewProjMatrix, uint shader);

	void SetBuffers(const ModelVertex* vertexData, const uint& vertexDataCount, const uint* indexData, const uint& indexDataCount);
	void SetBuffers(const std::vector<ModelVertex>& vertexData, const std::vector<uint>& indexData);
	
	// debug tool to create a box mesh.
	void MakeBox(const glm::vec3& boxMin, const glm::vec3& boxMax);

	// Link this mesh with a meshAsset.
	bool Initialize(const MeshAsset* inMeshAsset);

private:
	// indexes of the opengl buffers
	uint vertexBuffer;
	uint indexBuffer;

	// assets.
	const MeshAsset* meshAsset;

	// fast access data pointer. Only use after initalization. Supports direct acces to asset data.
	MeshDataPointers meshData;
	
	// Count of elements in to render
	int Count;
};

