#include "GameObject.h"

GameObject::~GameObject()
{
	
}

// Function to load meshes from filename
void GameObject::loadMeshes(const std::string & filename)
{
	loadMeshFromFile(filename, m_Meshes);
}
// Function to load texture from filename
void GameObject::loadDiffuseMap(const std::string & filename)
{
	m_DiffuseMapID = loadTextureFromFile(filename);
}

// set the shaderprogram ID by loading a vertex and fragment shader
void GameObject::loadShaderProgram(const std::string & vertFilename, const std::string & fragFilename)
{
	m_ShaderProgramID = LoadShaders(vertFilename.c_str(), fragFilename.c_str());
}

// preRender bind the active texture and use the shader program for the main file
void GameObject::preRender()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_DiffuseMapID);

	glUseProgram(m_ShaderProgramID);

	GLint textureLocation = glGetUniformLocation(m_ShaderProgramID, "baseTexture");

	glUniform1i(textureLocation, 0);

}
// Call the render function of Mesh
void GameObject::render()
{
	for (Mesh *pMesh : m_Meshes)
	{
		pMesh->render();
	}
}

// Destroy deletes the mesh, textures and program ID
void GameObject::destroy()
{
	glDeleteTextures(1, &m_DiffuseMapID);
	glDeleteProgram(m_ShaderProgramID);

	auto iter = m_Meshes.begin();
	while (iter != m_Meshes.end())
	{
		if ((*iter))
		{
			delete (*iter);
			iter = m_Meshes.erase(iter);
		}
		else
		{
			iter++;
		}
	}

}

// Default Constructor
GameObject::Transform::Transform()
{

	m_Position = glm::vec3(0.0f, 0.0f, 0.0f);
	m_Rotation = glm::vec3(0.0f, 0.0f, 0.0f);
	m_Scale = glm::vec3(1.0f, 1.0f, 1.0f);

	m_ModelMatrix = glm::mat4(1.0f);
}

// Set the gameobject position
void GameObject::Transform::setPosition(glm::vec3 & newPosition)
{
	m_Position = newPosition;
}

// Set the gameobject rotation
void GameObject::Transform::setRotation(glm::vec3 & newRotation)
{
	m_Rotation = newRotation;
}

// Set the gameobject scale
void GameObject::Transform::setScale(glm::vec3 & newScale)
{
	m_Scale = newScale;
}

// Update the model matrix based on position scale and rotation
void GameObject::Transform::update()
{
	glm::mat4 translationMatrix = glm::translate(m_Position);
	glm::mat4 scaleMatrix = glm::scale(m_Scale);
	glm::mat4 rotationMatrix =
		glm::rotate(m_Rotation.x, glm::vec3(1.0f, 0.0f, 0.0f)) *
		glm::rotate(m_Rotation.y, glm::vec3(0.0f, 1.0f, 0.0f)) *
		glm::rotate(m_Rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));

	m_ModelMatrix = translationMatrix*rotationMatrix*scaleMatrix;
}

// get the gameobject position
glm::vec3 GameObject::Transform::getPosition()
{
	return m_Position;
}

// get the gameobject rotation
glm::vec3 GameObject::Transform::getRotation()
{
	return m_Rotation;
}

// get the gameobject scale
glm::vec3 GameObject::Transform::getScale()
{
	return m_Scale;
}

// get the gameobject model matrix
glm::mat4 GameObject::Transform::getModelMatrix()
{
		return m_ModelMatrix;
}

// Default Contructor for lighting
GameObject::Lighting::Lighting()
{
	m_SpecularPower = 25.0f;
	
	m_LightDirection = glm::vec3(0.0f,0.0f,5.0f);
	
	m_DiffuseLightColour = glm::vec4(0.0f, 0.3f, 0.3f,1.0f);
	m_DiffuseMaterialColour = glm::vec4(1.0f, 0.0f, 0.0f,1.0f);

	m_SpecularLightColour = glm::vec4(0.3f, 0.3f, 0.3f, 1.0f);
	m_SpecularMaterialColour = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
}


// Sends all the lighting data
void GameObject::Lighting::sendLightingData()
{
	GLuint lightDirectionLocation = glGetUniformLocation(parentRef->getShaderProgramID(), "lightDirection");
	GLuint diffuseLightColourLocation = glGetUniformLocation(parentRef->getShaderProgramID(), "diffuseLightColour");
	GLuint diffuseMaterialColourLocation = glGetUniformLocation(parentRef->getShaderProgramID(), "diffuseMaterialColour");

	GLuint specularLightColourLocation = glGetUniformLocation(parentRef->getShaderProgramID(), "specularLightColour");
	GLuint specularMaterialColourLocation = glGetUniformLocation(parentRef->getShaderProgramID(), "specularMaterialColour");
	GLuint specularPowerLocation = glGetUniformLocation(parentRef->getShaderProgramID(), "specularPower");

	glUniform3fv(lightDirectionLocation, 1, value_ptr(m_LightDirection));
	glUniform4fv(diffuseLightColourLocation, 1, value_ptr(m_DiffuseLightColour));
	glUniform4fv(diffuseMaterialColourLocation, 1, value_ptr(m_DiffuseMaterialColour));

	glUniform4fv(specularLightColourLocation, 1, value_ptr(m_SpecularLightColour));
	glUniform4fv(specularMaterialColourLocation, 1, value_ptr(m_SpecularMaterialColour));
	glUniform1f(specularPowerLocation, m_SpecularPower);
}

// Set the lighting direction
void GameObject::Lighting::setLightDirection(glm::vec3 newLightDirection)
{
	m_LightDirection = newLightDirection;
}

// Set the diffuse light colour
void GameObject::Lighting::setDiffuseLightColour(glm::vec4 newDiffuseLightColour)
{
	m_DiffuseLightColour = newDiffuseLightColour;
}

// Set the diffuse material colour
void GameObject::Lighting::setDiffuseMaterialColour(glm::vec4 newDiffuseMaterialColour)
{
	m_DiffuseMaterialColour = newDiffuseMaterialColour;
}

// Set the specular light colour
void GameObject::Lighting::setSpecularLightColour(glm::vec4 newSpecularLightColour)
{
	m_SpecularLightColour = newSpecularLightColour;
}

// Set the specular Material Colour
void GameObject::Lighting::setSpecularMaterialColour(glm::vec4 newSpecularMaterialColour)
{
	m_SpecularMaterialColour = newSpecularMaterialColour;
}

// Set the ambient material colour
void GameObject::Lighting::setAmbientMaterialColour(glm::vec4 newAmbientMaterialColour)
{
	m_AmbientMaterialColour = newAmbientMaterialColour;
}

// Set the gameobject mass
void GameObject::Physics::setMass(float mass)
{
	gameObjectMass = mass;
}

// Set the gameobject Inertia
void GameObject::Physics::setInertia(float x, float y, float z)
{
	gameObjectInertia = btVector3(x, y, z);
}

// Set the gameobject collision box size
void GameObject::Physics::setCollisionBoxSize(float x, float y, float z)
{
	gameObjectCollisionShape = new btBoxShape(btVector3(x, y, z));
}

// generate the rigid body for the gameobject
void GameObject::Physics::enablePhysics(float originX, float originY, float originZ)
{
	gameObjectTransform.setIdentity();
	gameObjectTransform.setOrigin(btVector3(originX,originY,originZ));

	gameObjectCollisionShape->calculateLocalInertia(gameObjectMass, gameObjectInertia);

	gameObjectMotionState = new btDefaultMotionState(gameObjectTransform);
	btRigidBody::btRigidBodyConstructionInfo gameObjectRBInfo(gameObjectMass, gameObjectMotionState, gameObjectCollisionShape, gameObjectInertia);
	gameObjectRigidBody = new btRigidBody(gameObjectRBInfo);
}

// Update the physics and set the gameobject position to the new location
void GameObject::Physics::updatePhysics()
{
	gameObjectTransform = gameObjectRigidBody->getWorldTransform();
	rigidbodyOrigin = gameObjectTransform.getOrigin();
	gameObjectOrientation = gameObjectTransform.getRotation();

	parentRef->Transform.setPosition(glm::vec3(rigidbodyOrigin.getX(), rigidbodyOrigin.getY(), rigidbodyOrigin.getZ()));

}

// Delete the gameobject collision shape
void GameObject::Physics::disablePhysics()
{
	delete gameObjectCollisionShape;
}

// get the rigid body
btRigidBody * GameObject::Physics::getRigidBody()
{
	return gameObjectRigidBody;
}
