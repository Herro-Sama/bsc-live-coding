#pragma once

#include <vector>

#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include <glm\gtc\type_ptr.hpp>

#include "model.h"
#include "texture.h"
#include "shader.h"

class GameObject
{
public:
	GameObject() : Lighting(this) 
	{
		m_Meshes.clear();
		m_ShaderProgramID = 0;
	}
	~GameObject();

	class Transform
	{
	public:
		Transform(GameObject * ref) : parentRef_(ref){}
		Transform();


		void setPosition(glm::vec3& newPosition);
		void setRotation(glm::vec3& newRotation);
		void setScale(glm::vec3& newScale);

		void update();

		glm::vec3 getPosition();
		glm::vec3 getRotation();
		glm::vec3 getScale();

		glm::mat4 getModelMatrix();


	private:
		GameObject * parentRef_;

		glm::vec3 m_Position;
		glm::vec3 m_Scale;
		glm::vec3 m_Rotation;

		glm::mat4 m_ModelMatrix;

	}Transform;	

	class Lighting
	{
	public:
		Lighting(GameObject * ref) : parentRef(ref) {}
		Lighting();


		void sendLightingData();

		void setLightDirection(glm::vec3 newLightDirection);
		void setDiffuseLightColour(glm::vec4 newDiffuseLightColour);
		void setDiffuseMaterialColour(glm::vec4 newDiffuseMaterialColour);
		void setSpecularLightColour(glm::vec4 newSpecularLightColour);
		void setSpecularMaterialColour(glm::vec4 newSpecularMaterialColour);
		void setAmbientMaterialColour(glm::vec4 newAmbientMaterialColour);

	private:
		GameObject * parentRef;

		float m_SpecularPower;

		glm::vec3 m_LightDirection;

		glm::vec4 m_DiffuseLightColour;

		glm::vec4 m_DiffuseMaterialColour;

		glm::vec4 m_SpecularLightColour;

		glm::vec4 m_SpecularMaterialColour;

		glm::vec4 m_AmbientMaterialColour;

	}Lighting;

	GLuint getShaderProgramID()
	{
		return m_ShaderProgramID;
	}

	void loadMeshes(const std::string& filename);
	void loadDiffuseMap(const std::string& filename);
	void loadShaderProgram(const std::string& vectFilename, const std::string& fragFilename);

	void preRender();

	void render();

	void destroy();

private:
	std::vector<Mesh*> m_Meshes;

	GLuint m_DiffuseMapID;

	GLuint m_ShaderProgramID;

};
