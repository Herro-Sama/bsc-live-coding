//main.cpp - defines the entry point of the application

#include "main.h"

int main(int argc, char* args[])
{
	//Initialises the SDL Library, passing in SDL_INIT_VIDEO to only initialise the video subsystems
	//https://wiki.libsdl.org/SDL_Init
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		//Display an error message box
		//https://wiki.libsdl.org/SDL_ShowSimpleMessageBox
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, SDL_GetError(), "SDL_Init failed", NULL);
		return 1;
	}

	//Create a window, note we have to free the pointer returned using the DestroyWindow Function
	//https://wiki.libsdl.org/SDL_CreateWindow
	SDL_Window* window = SDL_CreateWindow("SDL2 Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
	//Checks to see if the window has been created, the pointer will have a value of some kind
	if (window == nullptr)
	{
		//Show error
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, SDL_GetError(), "SDL_CreateWindow failed", NULL);
		//Close the SDL Library
		//https://wiki.libsdl.org/SDL_Quit
		SDL_Quit();
		return 1;
	}

	//lets ask for a 3.2 core profile version of OpenGL
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	SDL_GLContext GL_Context = SDL_GL_CreateContext(window);
	if (GL_Context == nullptr)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, SDL_GetError(), "SDL GL Create Context failed", NULL);
		SDL_DestroyWindow(window);
		SDL_Quit();
		return 1;
	}
	//Initialize GLEW
	glewExperimental = GL_TRUE;
	GLenum glewError = glewInit();
	if (glewError != GLEW_OK)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, (char*)glewGetErrorString(glewError), "GLEW Init Failed", NULL);
	}

	std::vector<GameObject *> gameObjectList;

	GameObject * soldier = new GameObject();

	soldier->loadMeshes("basicCharacter.fbx");
	soldier->loadDiffuseMap("skin_soldier.png");

	soldier->setPosition(glm::vec3(50.0f, 50.0f, 50.0f));
	soldier->setScale(glm::vec3(1.0f, 1.0f, 5.0f));
	soldier->setRotation(glm::vec3(0.0f, -2.0f, 0.0f));

	soldier->update();

	soldier->loadShaderProgram("TextureVert.glsl", "TextureFrag.glsl");

	gameObjectList.push_back(soldier);

	soldier = new GameObject();

	soldier->loadMeshes("basicCharacter.fbx");
	soldier->loadDiffuseMap("skin_soldier.png");

	soldier->setPosition(glm::vec3(50.0f, 50.0f, 50.0f));
	soldier->setScale(glm::vec3(2.0f, 2.0f, 2.0f));
	soldier->setRotation(glm::vec3(0.0f, 2.0f, 0.0f));

	soldier->update();

	soldier->loadShaderProgram("TextureVert.glsl", "TextureFrag.glsl");

	gameObjectList.push_back(soldier);

	soldier = new GameObject();

	soldier->loadMeshes("basicCharacter.fbx");
	soldier->loadDiffuseMap("skin_soldier.png");

	soldier->setPosition(glm::vec3(50.0f, 50.0f, 50.0f));
	soldier->setScale(glm::vec3(3.0f, 7.5f, 1.0f));
	soldier->setRotation(glm::vec3(0.0f, 5.0f, 0.0f));

	soldier->update();

	soldier->loadShaderProgram("TextureVert.glsl", "TextureFrag.glsl");

	gameObjectList.push_back(soldier);

	int xpos = 0, ypos = 0;

	vec3 cameraPosition = vec3(0.0f, 0.0f, -10.0f);
	vec3 cameraTarget = vec3(0.0f, 0.0f, 0.0f);
	vec3 cameraUp = vec3(0.0f, 1.0f, 0.0f);

	mat4 viewMatrix = lookAt(cameraPosition, cameraTarget, cameraUp);

	//Lighting Stuff
	vec3 lightDirection = vec3(0.0f, 0.0f, 1.0f);
	vec4 diffuseLightColour = vec4(0.0f, 1.0f, 1.0f, 1.0f);

	//Material Stuff
	vec4 diffuseMaterialColour = vec4(0.8f, 0.8f, 0.8f, 1.0f);

	// position
	glm::vec3 position = glm::vec3(0, 0, 5);
	// horizontal angle : toward -Z
	float horizontalAngle = 3.14f;
	// vertical angle : 0, look at the horizon
	float verticalAngle = 0.0f;
	// Initial Field of View
	float initialFoV = 45.0f;

	float speed = 3.0f; // 3 units / second
	float mouseSpeed = 0.005f;

	mat4 projectionMatrix = perspective(radians(90.0f), float(4.0f / 3.0f), 0.1f, 100.0f);


	GLint lightDirectionLocation = glGetUniformLocation(soldier->getShaderProgramID(), "lightDirection");
	GLint diffuselightColourLocation = glGetUniformLocation(soldier->getShaderProgramID(), "diffuseLightColour");

	//GLuint programID = LoadShaders("TextureVert.glsl", "TextureFrag.glsl");

	/*GLint fragColourLocation=glGetUniformLocation(programID, "fragColour");
	if (fragColourLocation < 0)
	{
		printf("Unable to find %s uniform\n", "fragColour");
	}

	static const GLfloat fragColour[] = { 0.0f,1.0f,0.0f,1.0f };

	GLint currentTimeLocation= glGetUniformLocation(programID, "time");
	if (currentTimeLocation < 0)
	{
		printf("Unable to find %s uniform\n", "time");
	}

	*/
	
	//GLint modelMatrixLocation = glGetUniformLocation(programID, "modelMatrix");
	//GLint viewMatrixLocation = glGetUniformLocation(soldier->getShaderProgramID(), "viewMatrix");
	//GLint projectionMatrixLocation = glGetUniformLocation(soldier->getShaderProgramID(), "projectionMatrix");
	//GLint textureLocation = glGetUniformLocation(programID, "baseTexture");
	//GLint lightDirectionLocation = glGetUniformLocation(soldier->getShaderProgramID(), "lightDirection");
	//GLint diffuselightColourLocation = glGetUniformLocation(soldier->getShaderProgramID(), "diffuseLightColour");
	//GLint diffuseMaterialColourLocation = glGetUniformLocation(programID, "diffuseMaterialColour");


	glEnable(GL_DEPTH_TEST);
	int lastTicks = SDL_GetTicks();
	int currentTicks = SDL_GetTicks();


	//Event loop, we will loop until running is set to false, usually if escape has been pressed or window is closed
	bool running = true;
	//SDL Event structure, this will be checked in the while loop
	SDL_Event ev;
	while (running)
	{
		//Poll for the events which have happened in this frame
		//https://wiki.libsdl.org/SDL_PollEvent
		while (SDL_PollEvent(&ev))
		{
			//Switch case for every message we are intereted in
			switch (ev.type)
			{
				//QUIT Message, usually called when the window has been closed
			case SDL_QUIT:
				running = false;
				break;
				//KEYDOWN Message, called when a key has been pressed down
			case SDL_KEYDOWN:
				//Check the actual key code of the key that has been pressed
				switch (ev.key.keysym.sym)
				{
					//Escape key
				case SDLK_ESCAPE:
					running = false;
					break;

				case SDLK_w:
					cameraPosition.z += 0.5;
					cameraTarget.z += 0.5;
					break;

				case SDLK_s:
					cameraPosition.z -= 0.5;
					cameraTarget.z -= 0.5;
					break;

				case SDLK_a:
					cameraPosition.x += 0.5;
					cameraTarget.x += 0.5;
					break;

				case SDLK_d:
					cameraPosition.x -= 0.5;
					cameraTarget.x -= 0.5;
					break;

				case SDLK_LCTRL:
					cameraPosition.y -= 0.5;
					cameraTarget.y -= 0.5;
					break;

				case SDLK_SPACE:
					cameraPosition.y += 0.5;
					cameraTarget.y += 0.5;
					break;



				}
			}
		}

		//SDL_SetRelativeMouseMode(SDL_bool(SDL_ENABLE));

		currentTicks = SDL_GetTicks();
		float deltaTime = (float)(currentTicks - lastTicks) / 1000.0f;

		SDL_GetRelativeMouseState(&xpos, &ypos);
		//printf("Mouse %i %i \n", xpos, ypos);

		horizontalAngle += mouseSpeed * deltaTime * float(xpos);
		verticalAngle += mouseSpeed * deltaTime * float(ypos);

		vec3 direction
		(	
			cos(verticalAngle) * sin(horizontalAngle),
			sin(verticalAngle),
			cos(verticalAngle) * cos(horizontalAngle)
		);

		vec3 right = vec3
		(
			sin(horizontalAngle - 3.14f / 2.0f),
			0,
			cos(horizontalAngle - 3.14f / 2.0f)
		);

		vec3 up = cross(right, direction);

		viewMatrix = lookAt(cameraPosition, glm::vec3(5.0f,0.0f,0.0f), cameraUp);

		cameraTarget = direction;

		for (GameObject * pCurrentObj : gameObjectList)
	{
		pCurrentObj->update();
	}


		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClearDepth(1.0f);
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

		for (GameObject * pCurrentObj : gameObjectList)
		{

			mat4 MVPMatrix = projectionMatrix * viewMatrix * pCurrentObj->getModelMatrix();


			pCurrentObj->preRender();

			GLint viewMatrixLocation = glGetUniformLocation(pCurrentObj->getShaderProgramID(), "viewMatrix");
			GLint projectionMatrixLocation = glGetUniformLocation(pCurrentObj->getShaderProgramID(), "projectionMatrix");

			GLint MVPMatrixLocation = glGetUniformLocation(pCurrentObj->getShaderProgramID(), "MVPMatrix");

			glUniformMatrix4fv(MVPMatrixLocation, 1, GL_FALSE, &MVPMatrix[0][0]);
			glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, value_ptr(viewMatrix));
			glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, value_ptr(projectionMatrix));

			pCurrentObj->render();
		}


		//glActiveTexture(GL_TEXTURE0);
		//glBindTexture(GL_TEXTURE_2D, textureID);

		//glUseProgram(programID);

		//glUniform4fv(fragColourLocation, 1, fragColour);
		//glUniform1f(currentTimeLocation, (float)(currentTicks)/1000.0f);
		

		//glUniform1i(textureLocation, 0);

		glUniform3fv(lightDirectionLocation, 1, value_ptr(lightDirection));
		glUniform4fv(diffuselightColourLocation, 1, value_ptr(diffuseLightColour));

		//glUniform4fv(diffuseMaterialColourLocation, 1, value_ptr(diffuseMaterialColour));

		//for (Mesh *pMesh : meshes)
		//{
		//	pMesh->render();
		//}
		SDL_GL_SwapWindow(window);

		lastTicks = currentTicks;
	}

	/*auto iter = meshes.begin();
	while (iter != meshes.end())
	{
		if ((*iter))
		{
			delete (*iter);
			iter = meshes.erase(iter);
		}
		else
		{
			iter++;
		}
	}*/

	/*meshes.clear();
	glDeleteTextures(1, &textureID);
	glDeleteProgram(programID);*/
	
	auto iter = gameObjectList.begin();
	while (iter != gameObjectList.end())
	{
		if ((*iter))
		{
			(*iter)->destroy();
			delete (*iter);
			(*iter) = nullptr;
			iter = gameObjectList.erase(iter);
		}

	}
	
	SDL_GL_DeleteContext(GL_Context);
	//Destroy the window and quit SDL2, NB we should do this after all cleanup in this order!!!
	//https://wiki.libsdl.org/SDL_DestroyWindow
	SDL_DestroyWindow(window);
	//https://wiki.libsdl.org/SDL_Quit
	SDL_Quit();

	return 0;
}