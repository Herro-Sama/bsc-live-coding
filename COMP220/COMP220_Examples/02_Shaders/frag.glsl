#version 330 core

in vec4 vertexColourOut;

out vec4 Colour;

uniform vec4 fragColour=vec4(1.0, 1.0, 1.0, 1.0);

void main()
{
	Colour=vertexColourOut;
}