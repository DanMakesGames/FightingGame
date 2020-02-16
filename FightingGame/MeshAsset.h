#pragma once
#include "Asset.h"

// info needed to be sent to the 
struct ModelVertex {
	glm::vec3 position;
	glm::vec3 normal;
};

struct ModelDataPointers
{
	const ModelVertex* vertices;
	const uint* triangles;

	ModelDataPointers(ModelVertex* inVertices, uint* inTriangle) : vertices(inVertices), triangles(inTriangle)
	{

	}
};

class MeshAsset : public Asset
{
public:
	void InitMesh(uint inIndex, const aiMesh* inAiMesh);
private:
	std::vector<ModelVertex> vertices;

	// aka the indices in order.
	std::vector<uint> triangles;

	std::vector<glm::mat4> BindingMatricies;
};

