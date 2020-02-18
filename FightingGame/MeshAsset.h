#pragma once
#include "Asset.h"

// info needed to be sent to the 
struct ModelVertex {
	glm::vec3 position;
	glm::vec3 normal;
};

struct MeshDataPointers
{
	const ModelVertex* vertices;
	uint verticesCount;

	const uint* indices;
	uint indicesCount;

	MeshDataPointers() : vertices(nullptr), verticesCount(0), indices(nullptr), indicesCount(0) 
	{
	}

	MeshDataPointers(const ModelVertex* inVertices, const uint& inVerticesCount, const uint* inTriangle, const uint& inIndiciesCount) : vertices(inVertices), indices(inTriangle), verticesCount(inVerticesCount), indicesCount(inIndiciesCount)
	{
	}

	MeshDataPointers(const MeshDataPointers& inData) : vertices(inData.vertices), verticesCount(inData.verticesCount), indices(inData.indices), indicesCount(inData.indicesCount)
	{
	}

	MeshDataPointers& operator=(MeshDataPointers other)
	{
		vertices = other.vertices;
		verticesCount = other.verticesCount;

		indices = other.indices;
		indicesCount = other.indicesCount;
		return *this;
	}

};

class MeshAsset
{
public:
	void InitMesh(uint inIndex, const aiMesh* inAiMesh);

	MeshDataPointers GetMeshDataPointers() const;

private:
	std::vector<ModelVertex> vertices;

	// aka the indices in order.
	// this really should just be called "indices" but im too lazy to change it.
	std::vector<uint> triangles;

	std::vector<glm::mat4> BindingMatricies;
};

