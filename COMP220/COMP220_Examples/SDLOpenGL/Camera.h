#pragma once
#include<GL/glew.h>
#include<glm/glm.hpp>
#include <iostream>
using namespace glm;
class Camera
{
public:
	vec3 worldPos = vec3(40.0f, 5.0f, 40.0f);  //pos of the camera
	vec3 centre = vec3(45.0f, 0.0f, 45.0f);   //point the camera looks at
	vec3 up = vec3(0.0f, 1.0f, 0.0f);		 //the up direction of the camera(where is directly above of the camera)
	vec3 forward = normalize(centre - worldPos);
	vec3 right = cross(up, forward);
	vec3 centreMag = (centre - worldPos);

	float length = centreMag.length();
	void strafe(float);
	void move(float);
	void lift(float);
	void rotate(float, float);
private:
	float mouseSens = 200.0;
	float TurnDegreesFromOriginX = 90.0f;
	float TurnDegreesFromOriginY= 0.0;
};