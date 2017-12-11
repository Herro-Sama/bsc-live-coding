#include "Light.h"

void Light::init(GLuint programID)
{
	staticMesh.init("only_quad_sphere.txt", programID);
	staticMesh.worldPos = location;
}

void Light::render(Camera &camera)
{
	staticMesh.worldPos = location;
	staticMesh.worldRot = rotation;
	staticMesh.worldScale = scale;
	staticMesh.render(camera);
}

void Light::moveCircle()
{
	angle += 0.005;
	location.x += 0.1 *sin(angle);
	location.y += 0.1 *cos(angle);
}
