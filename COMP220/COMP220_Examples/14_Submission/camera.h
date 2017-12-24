#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

class Camera
{
public:
	Camera(float initalAspectRatio, glm::vec3& location = glm::vec3(40.0f, 5.0f, 40.0f), glm::vec3& target = glm::vec3(-20.0f, 0.0f, -20.0f), glm::vec3& up = glm::vec3(0.0f, 1.0f, 0.0f));

	glm::vec3 forward = glm::normalize(target - worldPosition);

	glm::vec3 right = glm::cross(upDirection, forward);

	glm::vec3 centreMag = (target - worldPosition);

	glm::mat4 cameraMatrix;

	float length = centreMag.length();

	float aspectRatio;

	void strafe(float x);

	void move(float z);

	void lift(float y);

	void rotate(float x, float y);

	void setWorldPos(glm::vec3& newWorldPosistion) { worldPosition = newWorldPosistion; };

	glm::vec3& getworldPosition() { return worldPosition; };

	void setTarget(glm::vec3& newTarget) { target = newTarget;};

	glm::vec3& getCentre() { return target; };

	void setUp(glm::vec3 newUpDirection) { upDirection = newUpDirection; };

	glm::vec3& getUp() { return upDirection; };

private:

	glm::vec3 worldPosition = glm::vec3(40.0f, 5.0f, 40.0f);

	glm::vec3 target = glm::vec3(45.0f, 0.0f, 0.0f);

	glm::vec3 upDirection = glm::vec3(0.0f, 1.0f, 0.0f);
	
	void update();

	float mouseSensitivity = 200.0f;

};