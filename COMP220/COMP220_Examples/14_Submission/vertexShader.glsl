#version 330 core

layout(location=0) in vec3 vertexPosition;
layout(location=1) in vec4 TriangleColour;

uniform mat4 MVPMatrix = mat4(1.0f);

//out vec4 TriangleColour;

void main()
{
	vec4 modelVertexPosition = MVPMatrix * vec4(vertexPosition, 1.0f);

	gl_Position = modelVertexPosition;

}