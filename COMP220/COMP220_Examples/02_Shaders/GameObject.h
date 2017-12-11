#pragma once

#include <vector>

#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include <glm\gtc\type_ptr.hpp>

#include "Model.h"
#include "Mesh.h"
#include "Texture.h"
#include "Shader.h"

class GameObject
{
public:
	GameObject();
	~GameObject();
	
	void setPosition(const glm::vec3& position)
	{
		m_Position = position;
	};
	glm::vec3& GetPosition()
	{
		return m_Position;
	};

	void setScale(const glm::vec3& scale)
	{
		m_Scale = scale;
	};
	glm::vec3& GetScale()
	{
		return m_Scale;
	};

	void setRotation(const glm::vec3& rotation)
	{
		m_Rotation = rotation;
	};
	glm::vec3& GetRotation()
	{
		return m_Rotation;
	};

	glm::mat4& getModelMatrix()
	{
		return m_ModelMatrix;
	};

	void setSpecularPower(float power)
	{
		m_SpecularPower = power;
	}
	float getSpecularPower()
	{
		return m_SpecularPower;
	}

	GLuint getShaderProgramID()
	{
		return m_ShaderProgramID;
	}

	void loadMeshes(const std::string& filename);
	void loadDiffuseMap(const std::string& filename);
	void loadShaderProgram(const std::string& vectFilename, const std::string& fragFilename);

	void update();

	void preRender();

	void render();

	void destroy();

private:
	std::vector<Mesh*> m_Meshes;
	
	glm::vec3 m_Position;
	glm::vec3 m_Scale;
	glm::vec3 m_Rotation;
	glm::mat4 m_ModelMatrix;

	GLuint m_DiffuseMapID;
	glm::vec4 m_AmbientMaterialColour;
	glm::vec4 m_DiffuseMaterialColour;
	glm::vec4 m_SpecularMaterialColour;
	float m_SpecularPower;
	GLuint m_ShaderProgramID;

};