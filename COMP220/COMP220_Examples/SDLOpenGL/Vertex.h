#pragma once
#include <glm/glm.hpp>

using namespace glm;
struct Vertex
{
	vec3 vertexPos;
	vec4 vertexCol;
	vec2 textureCoords;
	vec3 vertexNormals;
};
struct LineVertex
{
	vec3 vertexPos;
	vec4 vertexCol;
};