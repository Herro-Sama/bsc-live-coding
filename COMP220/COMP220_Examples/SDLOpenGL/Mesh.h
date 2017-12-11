#pragma once


#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>

#include <string>
#include <vector>
#include <iostream>

#include <GL\glew.h>
#include <SDL_opengl.h>

#include "Vertex.h"
#include "Camera.h"
#include "MVP.h"
#include "Transform.h"
#include "subMesh.h"
#include "Texture.h"

class Mesh
{
public:
	~Mesh();
	float aspectRatio = 4/3;
	vec3 worldPos =vec3(0.0f, 0.0f, 0.0f);
	vec3 worldRot = vec3(0.0f, 0.0f, 0.0f);
	vec3 worldScale = vec3(1.0f, 1.0f, 1.0f);
	void init(const std::string&, GLuint, bool = false, const std::string& = "" );
	void render(Camera&, vec3 = vec3(0.0f,0.0f,0.0f));
	void movement(float);
	std::vector<subMesh*> subMeshes;
	void copyBufferData();
	
private:
	Transform MVPMatrix;
	MVP MVPLoc;
	GLuint programToUse = 0;
	GLint lightDirectionLoc;
	GLint lightDistanceLoc;
	GLint cameraDirection;
	bool islitt;
	vec3 directionFromLightSource;
	vec3 lightSource;
	vec3 tempLightDir;
	float distanceToLight;
	GLuint textureID;
	bool hasTexture;
	GLint textureLocation;
};

bool loadMeshFromFile(const std::string&, std::vector<subMesh*>&);