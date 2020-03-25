#pragma once
#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"
#include "Core.h"
#include "MeshAsset.h"
#include "TextureAsset.h"
#include "MaterialAsset.h"
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

	void SetPrimativeBuffers(const ModelVertex* vertexData, const uint& vertexDataCount, const uint* indexData, const uint& indexDataCount);
	void SetPrimativeBuffers(const std::vector<ModelVertex>& vertexData, const std::vector<uint>& indexData);
	void SetTextureBuffers(const void* texData, const uint& texWidth, const uint& texHeight);

	
	// debug tool to create a box mesh.
	void MakeBox(const glm::vec3& boxMin, const glm::vec3& boxMax);

	// Link this mesh with a meshAsset.
	bool Initialize(const MeshAsset* inMeshAsset);
	bool Initialize(const MeshAsset* inMeshAsset, const TextureAsset* inTexAsset);
	bool Initialize(const MeshAsset* inMeshAsset, const MaterialAsset* inTexAsset);

private:
	// indexes of the opengl buffers
	uint vertexBuffer;
	uint indexBuffer;
	uint texBuffer;

	// assets.
	const MeshAsset* meshAsset;
	// null if no texture
	const TextureAsset* texAsset;
	// null if no mat. In that case default values will be used.
	const MaterialAsset* matAsset;

	// fast access data pointer. Only use after initalization. Supports direct acces to asset data.
	MeshDataPointers meshData;

	TextureData texData;
	
	// Count of elements in to render
	int Count;
};

