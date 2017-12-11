#pragma once

#include "Mesh.h"

class WorldObject
{
public:
	vec3 worldLocation = vec3(0.0f, 0.0f, 0.0f);
	vec3 worldRotation = vec3(0.0f, 0.0f, 0.0f);
	vec3 worldScale = vec3(1.0f, 1.0f, 1.0f);
	vec3 directionOfTravel = vec3(0.0, 0.0, 0.0);
	float speedOfTravel;
	float mass;
	bool hasGravity = true;
	void draw(Camera&, vec3& = vec3(0.0f,0.0f,0.0f));
	void update();
	void init(Mesh &meshAd);
private:
	Mesh* mesh;
	
};