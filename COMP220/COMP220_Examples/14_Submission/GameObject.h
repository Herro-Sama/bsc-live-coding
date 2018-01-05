#pragma once

#include <vector>

#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include <glm\gtc\type_ptr.hpp>

#include "model.h"
#include "texture.h"
#include "shader.h"
#include "transform.h"

class GameObject
{
public:
	GameObject();
	~GameObject();

	class Transform
	{
	public:
		Transform();
		Transform(GameObject * ref) : parentRef(ref){}

		void setPosition(glm::vec3& newPosition);
		void setRotation(glm::vec3& newRotation);
		void setScale(glm::vec3& newScale);

		void update();

		glm::vec3 getPosition();
		glm::vec3 getRotation();
		glm::vec3 getScale();

		glm::mat4 getModelMatrix();


	private:
		GameObject * parentRef;

		glm::vec3 m_Position;
		glm::vec3 m_Scale;
		glm::vec3 m_Rotation;

		glm::mat4 m_ModelMatrix;

	}Transform;	

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

	GLuint m_DiffuseMapID;
	glm::vec4 m_AmbientMaterialColour;
	glm::vec4 m_DiffuseMaterialColour;
	glm::vec4 m_SpecularMaterialColour;
	float m_SpecularPower;
	GLuint m_ShaderProgramID;

};
