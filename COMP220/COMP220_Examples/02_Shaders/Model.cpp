#include "Model.h"


bool loadModelFromFile(const std::string& filename, GLuint VBO, GLuint EBO, unsigned int& numberOfVerts, unsigned int& numberOfIndices)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(filename,aiProcessPreset_TargetRealtime_Fast|aiProcess_FlipUVs);

	if (scene == nullptr)
	{
		printf("Error Loading Model %s", importer.GetErrorString());
		return false;
	}

	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;

	for (unsigned int m = 0; m < scene->mNumMeshes; m++)
	{
		const aiMesh* currentAIMesh = scene->mMeshes[m];
		for (unsigned int v = 0; v < currentAIMesh->mNumVertices; v++)
		{
			const aiVector3D currentAIPosition = currentAIMesh->mVertices[v];

			Vertex ourVertex;
			ourVertex.x = currentAIPosition.x;
			ourVertex.y = currentAIPosition.y;
			ourVertex.z = currentAIPosition.z;

			ourVertex.r = 0.0f; ourVertex.g = 1.0f; ourVertex.b = 1.0f; ourVertex.a = 1.0f;
			ourVertex.tu = 0.0f; ourVertex.tv = 0.0f;

			if(currentAIMesh->HasTextureCoords(0))
			{

				const aiVector3D currentTextureCoords = currentAIMesh->mTextureCoords[0][v];
				ourVertex.tu = currentTextureCoords.x;
				ourVertex.tv = currentTextureCoords.y;

			}

			if (currentAIMesh->HasVertexColors(0))
			{

				const aiColor4D currentColourCoords = currentAIMesh->mColors[0][v];
				ourVertex.r = currentColourCoords.r;
				ourVertex.g = currentColourCoords.g;
				ourVertex.b = currentColourCoords.b;
				ourVertex.a = currentColourCoords.a;

			}


			vertices.push_back(ourVertex);
		}


		for (unsigned int f = 0; f < currentAIMesh->mNumFaces; f++)
		{
			const aiFace currentFace = currentAIMesh->mFaces[f];
			
			indices.push_back(currentFace.mIndices[0]);
			indices.push_back(currentFace.mIndices[1]);
			indices.push_back(currentFace.mIndices[2]);

		}
	}
	numberOfVerts = vertices.size();
	numberOfIndices = indices.size();

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, numberOfVerts * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, numberOfIndices * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

	return true;
}