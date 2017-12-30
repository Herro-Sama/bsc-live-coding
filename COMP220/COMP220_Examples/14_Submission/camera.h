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

	glm::vec3 m_Forward = glm::normalize(m_Target - m_WorldPosition);

	glm::vec3 m_Right = glm::cross(m_UpDirection, m_Forward);

	glm::mat4 cameraMatrix;

	float m_AspectRatio;

	void strafe(float x);

	void move(float z);

	void lift(float y);

	void rotate(float x, float y);

	void setWorldPos(glm::vec3& newWorldPosistion) { m_WorldPosition = newWorldPosistion; };

	glm::vec3& getworldPosition() { return m_WorldPosition; };

	void setTarget(glm::vec3& newTarget) { m_Target = newTarget;};

	glm::vec3& getTarget() { return m_Target; };

	void setUp(glm::vec3 newUpDirection) { m_UpDirection = newUpDirection; };

	glm::vec3& getUp() { return m_UpDirection; };

private:

	glm::vec3 m_WorldPosition = glm::vec3(40.0f, 5.0f, 40.0f);

	glm::vec3 m_Target = glm::vec3(45.0f, 0.0f, 0.0f);

	glm::vec3 m_UpDirection = glm::vec3(0.0f, 1.0f, 0.0f);

	glm::vec3 m_Rotation = glm::vec3(1.0f, 1.0f, 1.0f);
	
	void update();

	float m_MouseSensitivity = 200.0f;

};