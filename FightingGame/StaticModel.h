#pragma once
#include "GraphicsObject.h"
#include "Mesh.h"
#include "Core.h"

class StaticModel : public GraphicsObject
{
public:
	StaticModel();
	~StaticModel();
	
	void Draw(const glm::mat4& modelMatrix, const glm::mat4& viewProjMatrix, uint shader);
	bool LoadFromFile(std::string fileName);
	bool InitializeFromScene(const aiScene* scene);

private:
	std::string modelFileName;
	glm::vec3 worldPosition;
	glm::mat4 worldMatrix;
	glm::mat4 localMatrix;

	// group these all together.
	std::vector<Mesh> meshes;
};

