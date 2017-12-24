#version 330 core

layout(location=0) in vec3 vertexPosition;
layout(location=1) in vec4 vertexColour;
layout(location=2) in vec2 vertexTextureCoord;

uniform mat4 MVPMatrix;

out vec4 vertexColourOut;
out vec2 vertexTextureCoordOut;

void main()
{
	gl_Position = MVPMatrix * vec4(vertexPosition, 1.0f);

	vertexColourOut = vertexColour;
	vertexTextureCoordOut = vertexTextureCoord;
}