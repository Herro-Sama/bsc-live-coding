#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <iostream>
#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include <GL\glew.h>
#include <SDL_opengl.h>
#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Texture.h"
#include "Vertex.h"
#include "Camera.h"
#include "ObjLoader.h"
#include "Transform.h"
#include "ShaderLoader.h"
#include "MVP.h"
#include "Grid.h"
#include "Mesh.h"
#include "Light.h"
#include "WorldObject.h"

using namespace std;
using namespace glm;

SDL_Window* window;

SDL_GLContext glContext;

int SCREEN_WIDTH = 1200;
int SCREEN_HEIGHT = 800;
float aspectRatio = (SCREEN_WIDTH / SCREEN_HEIGHT);
Camera camera;


// initialises modules
bool Init();

//Deallocates memory and calls SDL closing functions
void Close();
