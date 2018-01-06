#include "GameObject.h"

GameObject::~GameObject()
{
	
}

void GameObject::loadMeshes(const std::string & filename)
{
	loadMeshFromFile(filename, m_Meshes);
}

void GameObject::loadDiffuseMap(const std::string & filename)
{
	m_DiffuseMapID = loadTextureFromFile(filename);
}

void GameObject::loadShaderProgram(const std::string & vertFilename, const std::string & fragFilename)
{
	m_ShaderProgramID = LoadShaders(vertFilename.c_str(), fragFilename.c_str());
}


void GameObject::preRender()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_DiffuseMapID);

	glUseProgram(m_ShaderProgramID);

	GLint textureLocation = glGetUniformLocation(m_ShaderProgramID, "baseTexture");

	glUniform1i(textureLocation, 0);

}

void GameObject::render()
{
	for (Mesh *pMesh : m_Meshes)
	{
		pMesh->render();
	}
}

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

GameObject::Transform::Transform()
{

	m_Position = glm::vec3(0.0f, 0.0f, 0.0f);
	m_Rotation = glm::vec3(0.0f, 0.0f, 0.0f);
	m_Scale = glm::vec3(1.0f, 1.0f, 1.0f);

	m_ModelMatrix = glm::mat4(1.0f);
}

void GameObject::Transform::setPosition(glm::vec3 & newPosition)
{
	m_Position = newPosition;
}

void GameObject::Transform::setRotation(glm::vec3 & newRotation)
{
	m_Rotation = newRotation;
}

void GameObject::Transform::setScale(glm::vec3 & newScale)
{
	m_Scale = newScale;
}

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

glm::vec3 GameObject::Transform::getPosition()
{
	return m_Position;
}

glm::vec3 GameObject::Transform::getRotation()
{
	return m_Rotation;
}

glm::vec3 GameObject::Transform::getScale()
{
	return m_Scale;
}

glm::mat4 GameObject::Transform::getModelMatrix()
{
		return m_ModelMatrix;
}

GameObject::Lighting::Lighting()
{
	m_SpecularPower = 25.0f;
	
	m_LightDirection = glm::vec3(0.0f,0.0f,5.0f);
	
	m_DiffuseLightColour = glm::vec4(0.0f, 0.3f, 0.3f,1.0f);
	m_DiffuseMaterialColour = glm::vec4(1.0f, 0.0f, 0.0f,1.0f);

	m_SpecularLightColour = glm::vec4(0.3f, 0.3f, 0.3f, 1.0f);
	m_SpecularMaterialColour = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
}

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

void GameObject::Lighting::setLightDirection(glm::vec3 newLightDirection)
{
	m_LightDirection = newLightDirection;
}

void GameObject::Lighting::setDiffuseLightColour(glm::vec4 newDiffuseLightColour)
{
	m_DiffuseLightColour = newDiffuseLightColour;
}

void GameObject::Lighting::setDiffuseMaterialColour(glm::vec4 newDiffuseMaterialColour)
{
	m_DiffuseMaterialColour = newDiffuseMaterialColour;
}

void GameObject::Lighting::setSpecularLightColour(glm::vec4 newSpecularLightColour)
{
	m_SpecularLightColour = newSpecularLightColour;
}

void GameObject::Lighting::setSpecularMaterialColour(glm::vec4 newSpecularMaterialColour)
{
	m_SpecularMaterialColour = newSpecularMaterialColour;
}

void GameObject::Lighting::setAmbientMaterialColour(glm::vec4 newAmbientMaterialColour)
{
	m_AmbientMaterialColour = newAmbientMaterialColour;
}
