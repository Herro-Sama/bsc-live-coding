#include "camera.h"

Camera::Camera(float initalAspectRatio, glm::vec3 & location, glm::vec3 & centre, glm::vec3 & up)
{
	aspectRatio = initalAspectRatio;

	this->worldPosition = location;

	this->centre = centre;

	this->upDirection = up;

	glm::mat4 cameraMatrix = lookAt(worldPosition, centre, upDirection);

	update();

}

void Camera::strafe(float x)
{
	glm::vec3 strafeDirection = right*x;

	worldPosition.x += strafeDirection.x;
	worldPosition.z += strafeDirection.z;

	centre.x += strafeDirection.x;
	centre.z += strafeDirection.z;

	update();
}

void Camera::move(float z)
{
	glm::vec3 moveDirection = forward * z;

	worldPosition.x += moveDirection.x;
	worldPosition.z += moveDirection.z;
	centre.x += moveDirection.x;
	centre.z += moveDirection.z;

	update();
}

void Camera::lift(float y)
{
	glm::vec3 liftDirection = upDirection * y;

	worldPosition.y += liftDirection.y;
	centre.y += liftDirection.y;

	update();
}

void Camera::rotate(float x, float y)
{
	update();
}

void Camera::update()
{
	forward = glm::normalize(centre - worldPosition);
	right = glm::cross(upDirection, forward);
	cameraMatrix = lookAt(worldPosition, centre, upDirection);
}
