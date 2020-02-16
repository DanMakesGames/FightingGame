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

// info needed to be sent to the 
struct ModelVertex {
	glm::vec3 position;
	glm::vec3 normal;
};

class Mesh
{
public:
	Mesh();
	~Mesh();

	void Draw(const glm::mat4 &modelMatrix, const glm::mat4 &viewProjMatrix, uint shader);
	void MakeBox(const glm::vec3& boxMin, const glm::vec3& boxMax);
	void SetBuffers(const std::vector<ModelVertex>& vertexData, const std::vector<uint>& indexData);

	void InitMesh(uint inIndex, const aiMesh* inAiMesh);

private:
	uint vertexBuffer;
	uint indexBuffer;
	
	std::vector<ModelVertex> vertices;
	
	// aka the indices in order.
	std::vector<uint> triangles;
	
	std::vector<glm::mat4> BindingMatricies;

	// Count of elements in to render
	int Count;
};

