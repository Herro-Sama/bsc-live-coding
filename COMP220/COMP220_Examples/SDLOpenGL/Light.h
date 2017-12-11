#pragma once


#include "Mesh.h"

class Light
{
public:
	vec3 location = vec3(20.0, 50.0, 0.0);
	vec3 rotation = vec3(0.0, 0.0, 0.0);
	vec3 scale = vec3(3.0, 3.0, 3.0);
	float intensity = 2.0f;
	void init(GLuint programID);
	void render(Camera&);
	void moveCircle();
private:
		Mesh staticMesh;
		int radius = 4;
		double angle = 0.1;
};