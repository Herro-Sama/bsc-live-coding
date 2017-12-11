#pragma once
#include "Grid.h"

void Grid::createGridVec(int numberX, int numberY, GLuint programID)
{
	LineShader = programID;
	MVPLineShaderLoc = { glGetUniformLocation(LineShader, "modelMatrix"),
		glGetUniformLocation(LineShader, "viewMatrix"),
		glGetUniformLocation(LineShader, "projectionMatrix") };
	glGenBuffers(1, &lineBuff);
	int startPosX = 0 - numberX / 2;
	int startPosY = 0 - numberY / 2;
	for (int i = startPosX; i < startPosX*-1; i++)
	{
		
		for (int j = startPosY; j < startPosY*-1; j++)
		{
			vec3 lineVert1 = vec3(i, -1, j);
			vec3 lineVert2 = vec3(i, -1, 0);
			vec3 lineVert3 = vec3(i, -1, j);
			vec3 lineVert4 = vec3(0, -1, j);
			vec4 col = vec4(0.5, 0.5, 0.5, 1.0);
			vec4 col1 = vec4(0.5, 0.5, 0.5, 1.0);
			if (j%10== 0)
			{
				col = vec4(0.1, 1.0, 0.1, 1.0);
			}
			if (i%10 == 0)
			{
				col1 = vec4(0.1, 1.0, 0.1, 1.0);
			}
			LineVertex lineVertex = { lineVert1, col1 };
			LineVertex lineVertex2 = { lineVert2, col1 };
			LineVertex lineVertex3 = { lineVert3, col };
			LineVertex lineVertex4 = { lineVert4, col };
			lineVerts.push_back(lineVertex);
			lineVerts.push_back(lineVertex2);
			lineVerts.push_back(lineVertex3);
			lineVerts.push_back(lineVertex4);
		}

	}
	copyBufferData();
}

void Grid::draw(Camera &camera, float aspectRatio)
{
	glUseProgram(LineShader);
	MVPMatrix = calculateTransform(camera, aspectRatio);
	glUniformMatrix4fv(MVPLineShaderLoc.modelMatrixLocation, 1, GL_FALSE, value_ptr(MVPMatrix.modelMatrix));
	glUniformMatrix4fv(MVPLineShaderLoc.viewMatrixLocation, 1, GL_FALSE, value_ptr(MVPMatrix.viewMatrix));
	glUniformMatrix4fv(MVPLineShaderLoc.projectionMatrixLocation, 1, GL_FALSE, value_ptr(MVPMatrix.projectionMatrix));
	glBindBuffer(GL_ARRAY_BUFFER, lineBuff);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(LineVertex), 0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(LineVertex), ((void*)offsetof(LineVertex, vertexCol)));
	glDrawArrays(GL_LINES, 0, lineVerts.size());

}

Grid::~Grid()
{
	glDeleteBuffers(1, &lineBuff);

}

void Grid::copyBufferData()
{
	glBindBuffer(GL_ARRAY_BUFFER, lineBuff);
	glBufferData(GL_ARRAY_BUFFER, lineVerts.size() * sizeof(LineVertex), &lineVerts[0], GL_STATIC_DRAW);
}
