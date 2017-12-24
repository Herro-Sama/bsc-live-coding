#pragma once

#include <string>
#include <vector>
#include <fstream>

#include <SDL.h>
#include <GL\glew.h>
#include <SDL_opengl.h>

#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include <glm\gtc\type_ptr.hpp>

#include "vertex.h"
#include "shader.h"

#include "camera.h"
#include "GameObject.h"

SDL_Window * window;
SDL_GLContext GL_Context;

Camera* sceneCamera;


int initSDL();

void deleteSDL();

void draw_Grid();


using namespace glm;