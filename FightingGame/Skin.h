#pragma once
#include "Mesh.h"

struct VertexWeight
{
	int joint;
	float weight;
};


class Skin :
	public Mesh
{
public:
private:
	std::vector<std::vector<VertexWeight>> vertexWeights;
};

