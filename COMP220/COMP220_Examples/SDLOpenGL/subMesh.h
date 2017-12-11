#pragma once

#include <string>
#include <vector>

#include <GL\glew.h>
#include <SDL_opengl.h>

#include "Vertex.h"

class subMesh
{
public:
	~subMesh()
	{
		glDeleteVertexArrays(1, &m_VAO);
		glDeleteBuffers(1, &m_VBO);
		glDeleteBuffers(1, &m_EBO);
	}
	std::vector<unsigned int> meshElementArray;
	std::vector <Vertex> meshVertex;
	void init();
	GLuint m_VBO;
	GLuint m_EBO;
	GLuint m_VAO;
	bool hasTexture;
	bool lightMe;
};