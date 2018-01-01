//main.cpp - defines the entry point of the application
//copy $(ProjectDir)\*.glsl $(OutDir)\*.glsl

#include "main.h"

int main(int argc, char* args[])
{
	initSDL();

	sceneCamera = new Camera((800 / 600),vec3(0.0f, 0.0f, -1.0f), vec3(5.0f, 5.0f, 5.0f));

	mat4 viewMatrix = sceneCamera->cameraMatrix;

	std::vector<GameObject *> gameObjectList;

	GameObject * soldier = new GameObject();

	soldier->loadMeshes("basicCharacter.fbx");
	soldier->loadDiffuseMap("skin_soldier.png");
	soldier->setPosition(glm::vec3(0.0f, 0.0f, 0.0f));
	soldier->setScale(glm::vec3(1.0f, 1.0f, 1.0f));
	
	soldier->update();

	soldier->loadShaderProgram("vertexShader.glsl", "fragmentShader.glsl");

	gameObjectList.push_back(soldier);

	soldier = new GameObject();

	soldier->loadMeshes("basicCharacter.fbx");
	soldier->loadDiffuseMap("skin_woman.png");
	soldier->setPosition(glm::vec3(10.0f, 0.0f, 0.0f));
	soldier->setScale(glm::vec3(1.0f, 1.0f, 1.0f));

	soldier->update();

	soldier->loadShaderProgram("lightVertexShader.glsl", "lightFragmentShader.glsl");

	gameObjectList.push_back(soldier);

	soldier = new GameObject();

	soldier->loadMeshes("basicCharacter.fbx");
	soldier->loadDiffuseMap("skin_man.png");
	soldier->setPosition(glm::vec3(-10.0f, 0.0f, 0.0f));
	soldier->setScale(glm::vec3(1.0f, 1.0f, 1.0f));

	soldier->update();

	soldier->loadShaderProgram("vertexShader.glsl", "fragmentShader.glsl");

	gameObjectList.push_back(soldier);

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	GLuint vertexBuffer;
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

	mat4 projectionMatrix = perspective(radians(90.0f), float(4.0f / 3.0f), 0.1f, 100.0f);

	int mouseXPosition = 0.0f;
	int mouseYPosition = 0.0f;
	
	// horizontal angle : toward -Z
	float horizontalAngle = 3.14f;
	// vertical angle : 0, look at the horizon
	float verticalAngle = 0.0f;
	// Initial Field of View
	float initialFoV = 90.0f;

	float speed = 3.0f; // 3 units / second
	float mouseSpeed = 0.005f;

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
					sceneCamera->move(0.5f);
					break;

				case SDLK_s:
					sceneCamera->move(-0.5f);
					break;

				case SDLK_a:
					sceneCamera->strafe(0.5f);
					break;

				case SDLK_d:
					sceneCamera->strafe(-0.5f);
					break;

				case SDLK_LCTRL:
					sceneCamera->lift(-0.5f);
					break;

				case SDLK_SPACE:
					sceneCamera->lift(0.5f);
					break;
				}
			}
		}

		SDL_GetRelativeMouseState(&mouseXPosition, &mouseYPosition);



		currentTicks = SDL_GetTicks();
		float deltaTime = (float)(currentTicks - lastTicks) / 1000.0f;

		if (mouseXPosition != 0 && mouseYPosition != 0)
		{
			horizontalAngle += mouseSpeed * deltaTime * float(mouseXPosition);
			verticalAngle += mouseSpeed * deltaTime * float(mouseYPosition);

			sceneCamera->rotate(float(mouseXPosition), float(mouseYPosition));
		}
		//Update Screenspace
		glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
		glClearDepth(1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



		viewMatrix = sceneCamera->cameraMatrix;

		for (GameObject * pCurrentObj : gameObjectList)
		{

			vec3 lightDirection = vec3(0.0f, 0.0f, 1.0f);

			vec4 diffuseLightColour = vec4(1.0f, 1.0f, 1.0f, 1.0f);

			vec4 diffuseMaterialColour = vec4(0.0f, 0.5f, 0.5f, 1.0f);


			mat4 MVPMatrix = projectionMatrix * viewMatrix * pCurrentObj->getModelMatrix();

			pCurrentObj->preRender();

			GLuint lightDirectionLocation = glGetUniformLocation(pCurrentObj->getShaderProgramID(), "lightDirection");
			GLuint diffuseLightColourLocation = glGetUniformLocation(pCurrentObj->getShaderProgramID(), "diffuseLightColour");
			GLuint diffuseMaterialColourLocation = glGetUniformLocation(pCurrentObj->getShaderProgramID(), "diffuseMaterialColour");

			glUniform3fv(lightDirectionLocation, 1, value_ptr(lightDirection));
			glUniform4fv(diffuseLightColourLocation, 1, value_ptr(diffuseLightColour));
			glUniform4fv(diffuseMaterialColourLocation, 1, value_ptr(diffuseMaterialColour));

			GLint modelMatrixLocation = glGetUniformLocation(pCurrentObj->getShaderProgramID(), "modelMatrix");

			mat4 ModelMatrix = pCurrentObj->getModelMatrix();

			glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, &ModelMatrix[0][0]);

			GLint MVPMatrixLocation = glGetUniformLocation(pCurrentObj->getShaderProgramID(), "MVPMatrix");

			glUniformMatrix4fv(MVPMatrixLocation, 1, GL_FALSE, &MVPMatrix[0][0]);



			pCurrentObj->render();

		}


		SDL_GL_SwapWindow(window);

		lastTicks = currentTicks;
	}

	glDeleteVertexArrays(1, &VertexArrayID);
	glDeleteBuffers(1, &vertexBuffer);

	delete sceneCamera;

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

	deleteSDL();

	return 0;
}

int initSDL()
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
	window = SDL_CreateWindow("SDL2 Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
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

	GL_Context = SDL_GL_CreateContext(window);
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
		return 1;
	}

	return 0;
}

void deleteSDL()
{
	SDL_GL_DeleteContext(GL_Context);
	//Destroy the window and quit SDL2, NB we should do this after all cleanup in this order!!!
	//https://wiki.libsdl.org/SDL_DestroyWindow
	SDL_DestroyWindow(window);
	//https://wiki.libsdl.org/SDL_Quit
	SDL_Quit();
}
