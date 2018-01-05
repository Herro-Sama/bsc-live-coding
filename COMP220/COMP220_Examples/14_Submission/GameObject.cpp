#include "GameObject.h"

GameObject::GameObject()
{
	m_Meshes.clear();

	m_DiffuseMapID = 0;

	m_AmbientMaterialColour = glm::vec4(0.4f, 0.4f, 0.4f, 1.0f);
	m_DiffuseMaterialColour = glm::vec4(0.6f, 0.6f, 0.6f, 1.0f);
	m_SpecularMaterialColour = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	m_SpecularPower = 25.0f;

	m_ShaderProgramID = 0;
}

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

void GameObject::update()
{
	/*glm::mat4 translationMatrix = glm::translate(m_Position);
	glm::mat4 scaleMatrix = glm::scale(m_Scale);
	glm::mat4 rotationMatrix =
		glm::rotate(m_Rotation.x, glm::vec3(1.0f, 0.0f, 0.0f)) *
		glm::rotate(m_Rotation.y, glm::vec3(0.0f, 1.0f, 0.0f)) *
		glm::rotate(m_Rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));

	m_ModelMatrix = translationMatrix*rotationMatrix*scaleMatrix;*/

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
