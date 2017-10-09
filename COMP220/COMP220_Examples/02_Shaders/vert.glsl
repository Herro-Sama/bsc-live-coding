#version 330 core

layout(location=0) in vec3 vertexPosition;

uniform float time;

out vec3 vertexLocation;

void main()
{
	vec3 newVertexPosition = vertexPosition;
	newVertexPosition.xyz += sin(time);
	vertexLocation = newVertexPosition;

	gl_Position=vec4(newVertexPosition,1.0);
	//gl_Position.xyz=vertexPostition;
	//gl_Position.w=1.0;
}