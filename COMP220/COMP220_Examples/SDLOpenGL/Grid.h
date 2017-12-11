#pragma once

#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Vertex.h"
#include "MVP.h"
#include"Transform.h"
#include "Camera.h"
#include <iostream>
#include "ShaderLoader.h"
using namespace std;
using glm::vec3;
using glm::vec4;

class Grid
{
	public:
		void draw(Camera&, float aspectRatio);
		void createGridVec(int, int, GLuint);
		~Grid();
		void copyBufferData();
	private:
		GLuint LineShader;
		vector<LineVertex> lineVerts;
		Transform MVPMatrix;
		GLuint lineBuff;
		MVP MVPLineShaderLoc;	
};
