#include "camera.h"

Camera::Camera(float initalAspectRatio, glm::vec3 & location, glm::vec3 & target, glm::vec3 & up)
{
	aspectRatio = initalAspectRatio;

	this->worldPosition = location;

	this->target = target;

	this->upDirection = up;

	glm::mat4 cameraMatrix = lookAt(worldPosition, target, upDirection);

	update();

}

void Camera::strafe(float x)
{
	glm::vec3 strafeDirection = right*x;

	worldPosition.x += strafeDirection.x;
	worldPosition.z += strafeDirection.z;

	target.x += strafeDirection.x;
	target.z += strafeDirection.z;

	update();
}

void Camera::move(float z)
{
	glm::vec3 moveDirection = forward * z;

	worldPosition.x += moveDirection.x;
	worldPosition.z += moveDirection.z;
	target.x += moveDirection.x;
	target.z += moveDirection.z;

	update();
}

void Camera::lift(float y)
{
	glm::vec3 liftDirection = upDirection * y;

	worldPosition.y += liftDirection.y;
	target.y += liftDirection.y;

	update();
}

void Camera::rotate(float x, float y)
{	
	target = worldPosition + length * glm::vec3(cos(x), y, sin(x));

	update();
}

void Camera::update()
{
	forward = glm::normalize(target - worldPosition);
	right = glm::cross(upDirection, forward);
	cameraMatrix = lookAt(worldPosition,target, upDirection);
}
