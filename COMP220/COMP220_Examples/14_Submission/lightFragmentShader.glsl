#version 330 core

in vec4 vertexColourOut;
in vec2 vertexTextureCoordOut;
in vec3 vertexNormalsOut;
in vec4 diffuse;

out vec4 Colour;

uniform vec4 fragColour=vec4(1.0,1.0,1.0,1.0);

uniform sampler2D baseTexture;

void main()
{
	Colour = diffuse;
}