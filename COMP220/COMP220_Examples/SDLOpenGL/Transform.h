#pragma once
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>
#include "Camera.h"
using namespace glm;

struct Transform
{
	mat4 modelMatrix;
	mat4 viewMatrix;
	mat4 projectionMatrix;
};

inline Transform calculateTransform(Camera& camera, float aspectRatio, vec3 &spawnLocation = vec3(0.0f, 0.0f, 0.0f), vec3 &spawnRotation = vec3(0.0f, 0.0f, 0.0f), vec3 &spawnScale = vec3(1.0f, 1.0f, 1.0f))
{

	vec3 trianglePosition = spawnLocation;
	mat4 translationMatrix = translate(trianglePosition);
	//create rotation matrix
	vec3 trianglRotation = spawnRotation;
	mat4 rotationXMatrix = rotate(trianglRotation.x, vec3(1.0f, 0.0f, 0.0f));
	mat4 rotationYMatrix = rotate(trianglRotation.y, vec3(0.0, 1.0f, 0.0f));
	mat4 rotationZMatrix = rotate(trianglRotation.z, vec3(0.0, 0.0f, 1.0f));
	mat4 rotationMatix = rotationZMatrix*rotationYMatrix*rotationXMatrix;

	//create scaling matrix
	vec3 scaleVec = spawnScale;
	mat4 ScalingMatrix = scale(scaleVec);


	mat4 modelMatrix = translationMatrix*rotationMatix*ScalingMatrix;

	mat4 cameraMatrix = lookAt(camera.worldPos, camera.centre, camera.up);

	mat4 projectionMatrix = perspective(radians(90.0f), aspectRatio, 0.1f, 200.0f);

	Transform finalTransform = { modelMatrix, cameraMatrix, projectionMatrix };
	return finalTransform;
}
