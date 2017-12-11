#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include "Vertex.h"

using namespace glm;
using namespace std;

bool objLoader2(const char * filename)
{
	FILE * file = fopen(filename, "r");
	if (file == NULL)
	{
		printf("Impossible to open the file !\n");
		return true;
	}
	vector <vec3> vertVec;
	char lineHeader[255];
	bool searching = true;
	int res = fscanf(file, "%s", lineHeader);
	while (searching)
	{
		if (res == EOF)
		{
			break; // EOF = End Of File. Quit the loop.
		}
		if (strcmp(lineHeader, "v") == 0)
		{
			for (int i = 0; i != NULL; i++)
			{
				cout << lineHeader[i] << endl;
			}
		}
	}
};

bool loadOBJ(const char * path, vector <Vertex> & out_vertices, vector<int> & elemtArray)
{
	vector<vec3> temp_vertices;
	std::vector< unsigned int > vertexIndices;
	FILE * file = fopen(path, "r");
	if (file == NULL) {
		printf("Impossible to open the file !\n");
		return false;
	}
	while (1)
	{
		char lineHeader[1028];
		// read the first word of the line
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
		{
			break; // EOF = End Of File. Quit the loop.
		}
		if (strcmp(lineHeader, "v") == 0)
		{
			vec3 vertex;

			fscanf(file, "%f %f %f", &vertex.x, &vertex.y, &vertex.z);
			temp_vertices.push_back(vertex);

		}
		if (strcmp(lineHeader, "f") == 0)
		{
			int vertexIndex[4], uvIndex[4], normalIndex[4];

			fscanf(file, "%d", &vertexIndex[0]);
			fscanf(file, "%d", &vertexIndex[1]);
			fscanf(file, "%d", &vertexIndex[2]);
			fscanf(file, "%d", &vertexIndex[3]);


			elemtArray.push_back(vertexIndex[2] - 1);
			elemtArray.push_back(vertexIndex[0] - 1);
			elemtArray.push_back(vertexIndex[1] - 1);


			elemtArray.push_back(vertexIndex[3] - 1);
			elemtArray.push_back(vertexIndex[0] - 1);
			elemtArray.push_back(vertexIndex[2] - 1);
		}
		if (strcmp(lineHeader, "z") == 0)
		{
			cout << "z found cya" << endl;
			break;
		}
	}
	int temp = 0;
	vec2 foob;
	//Added vertex data to vertex array with random colour
	for (unsigned int i = 0; i < temp_vertices.size(); i++)
	{
		temp++;
		vec3 vert = temp_vertices[i];
		vec4 vertexCol = vec4(sin(rand() % 90), sin(rand() % 90), sin(rand() % 90), 1);
		//vec4 vertexCol = vec4(0.5f, 0.5f, 0.5f, 1.0);
		if (temp == 0)
		{
			foob = vec2(0.0f, 0.0f);
		}
		if (temp == 1)
		{
			foob = vec2(1.0f, 0.0f);
		}
		if (temp == 2)
		{
			foob = vec2(1.0f, 1.0f);
		}
		if (temp == 3)
		{
			foob = vec2(0.0f, 1.0f);
			temp = 0;
		}
		Vertex foo = { vert, vertexCol, foob };
		out_vertices.push_back(foo);
		//cout << vertex.x << " : " << vertex.y << " : " << vertex.z << endl;
	}
}
