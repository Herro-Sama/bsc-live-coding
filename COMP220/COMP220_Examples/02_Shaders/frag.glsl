#version 330 core

out vec4 colour;

in vec3 vertexLocation;

uniform float time;

void main()
{
	colour=vec4(vertexLocation.x,vertexLocation.y,vertexLocation.z,1.0);
}