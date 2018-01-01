#include "camera.h"

Camera::Camera(float initalAspectRatio, glm::vec3 & location, glm::vec3 & target, glm::vec3 & up)
{
	m_AspectRatio = initalAspectRatio;

	this->m_WorldPosition = location;

	this->m_Target = target;

	this->m_UpDirection = up;

	glm::mat4 cameraMatrix = lookAt(m_WorldPosition, target, m_UpDirection);

	update();

}

void Camera::strafe(float x)
{
	glm::vec3 strafeDirection = m_Right*x;

	m_WorldPosition.x += strafeDirection.x;
	m_WorldPosition.z += strafeDirection.z;

	m_Target.x += strafeDirection.x;
	m_Target.z += strafeDirection.z;

	update();
}

void Camera::move(float z)
{
	glm::vec3 moveDirection = m_Forward * z;

	m_WorldPosition.x += moveDirection.x;
	m_WorldPosition.z += moveDirection.z;
	m_Target.x += moveDirection.x;
	m_Target.z += moveDirection.z;

	update();
}

void Camera::lift(float y)
{
	glm::vec3 liftDirection = m_UpDirection * y;

	m_WorldPosition.y += liftDirection.y;
	m_Target.y += liftDirection.y;

	update();
}

void Camera::rotate(float x, float y)
{	
	
	m_Target = glm::vec3(
		cos(y) * sin(x),
		sin(y),
		cos(y) * cos(x));

	update();
}

void Camera::update()
{
	m_Forward = glm::normalize(m_Target - m_WorldPosition);
	m_Right = glm::cross(m_UpDirection, m_Forward);
	cameraMatrix = lookAt(m_WorldPosition, m_Target, m_UpDirection);
}
