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
		
		// load UV coordinates.
		if (inAiMesh->mTextureCoords[0] != nullptr)
		{
			//DEBUG_PRINT("uv: "<< to_string(glm::vec3(inAiMesh->mTextureCoords[0][i].x, inAiMesh->mTextureCoords[0][i].y, inAiMesh->mTextureCoords[0][i].z)));
			vertices[i].UVCoord = glm::vec2(inAiMesh->mTextureCoords[0][i].x, inAiMesh->mTextureCoords[0][i].y);
		}
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

