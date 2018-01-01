#version 330 core

layout(location=0) in vec3 vertexPosition;
layout(location=1) in vec4 vertexColour;
layout(location=2) in vec2 vertexTextureCoord;
layout(location=3) in vec3 vertexNormals;

uniform mat4 MVPMatrix;
uniform mat4 modelMatrix;

out vec4 vertexColourOut;
out vec2 vertexTextureCoordOut;
out vec3 vertexNormalsOut;
out vec4 diffuse;

uniform vec3 lightDirection;
uniform vec4 diffuseLightColour;
uniform vec4 specularLightColour;

uniform vec4 diffuseMaterialColour;
uniform vec4 specularMaterialColour;

void main()
{
	gl_Position = MVPMatrix * vec4(vertexPosition, 1.0f);

	vec4 worldNormals = normalize(modelMatrix * vec4(vertexNormals, 0.0f));

	float nDotl = clamp(dot(worldNormals.xyz, lightDirection),0,1);

	diffuse = diffuseMaterialColour * diffuseLightColour * nDotl;

	vertexColourOut = vertexColour;
	vertexTextureCoordOut = vertexTextureCoord;
	vertexNormalsOut = vertexNormals;
}