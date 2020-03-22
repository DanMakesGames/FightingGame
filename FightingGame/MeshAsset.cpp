#include "MeshAsset.h"

void MeshAsset::InitMesh(uint inIndex, const aiMesh* inAiMesh)
{
	vertices.clear();

	if (!inAiMesh->HasPositions() || !inAiMesh->HasNormals())
	{
		return;
	}

	vertices.resize(inAiMesh->mNumVertices);

	for (uint i = 0; i < inAiMesh->mNumVertices; i++)
	{

		vertices[i].position = glm::vec3(inAiMesh->mVertices[i].x, inAiMesh->mVertices[i].y, inAiMesh->mVertices[i].z);
		vertices[i].normal = glm::vec3(inAiMesh->mNormals[i].x, inAiMesh->mNormals[i].y, inAiMesh->mNormals[i].z);
	}

	// load primatives
	triangles.clear();

	if (inAiMesh->HasFaces())
	{
		triangles.resize(long long int(inAiMesh->mNumFaces) * 3l);
		DEBUG_PRINT(inAiMesh->mNumFaces);
		for (uint i = 0; i < inAiMesh->mNumFaces; i++)
		{
			if (inAiMesh->mFaces[i].mNumIndices != POLYGON_INDEX_COUNT)
			{
				fprintf(stderr, "Error while loading mesh. Polygon with wrong number of indicies encountered.\n");
				return;
			}
			triangles.push_back(inAiMesh->mFaces[i].mIndices[0]);
			triangles.push_back(inAiMesh->mFaces[i].mIndices[1]);
			triangles.push_back(inAiMesh->mFaces[i].mIndices[2]);
		}
	}

	materialIndex = inAiMesh->mMaterialIndex;
}

MeshDataPointers MeshAsset::GetMeshDataPointers() const
{
	MeshDataPointers outMeshData(&(vertices[0]),vertices.size(), &(triangles[0]), triangles.size());
	return outMeshData;
}

