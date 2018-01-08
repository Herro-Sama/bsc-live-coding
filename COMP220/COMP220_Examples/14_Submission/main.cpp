//main.cpp - defines the entry point of the application
//copy $(ProjectDir)\*.glsl $(OutDir)\*.glsl

#include "main.h"

int main(int argc, char* args[])
{
	initSDL();
	initGLEW();

	sceneCamera = new Camera((800 / 600),vec3(-4.0f, 0.0f, -16.0f), vec3(5.0f, 5.0f, 5.0f));

	mat4 viewMatrix = sceneCamera->cameraMatrix;

	std::vector<GameObject *> gameObjectList;

	GameObject * soldier = new GameObject();

	soldier->loadMeshes("basicCharacter.fbx");
	soldier->loadDiffuseMap("skin_soldier.png");
	soldier->Transform.setPosition(glm::vec3(0.0f, 0.0f, 0.0f));
	soldier->Transform.setScale(glm::vec3(1.0f, 1.0f, 1.0f));

	soldier->Transform.update();

	soldier->Physics.setCollisionBoxSize(0.5f, 1.0f, 0.5f);

	soldier->Physics.setMass(0.0f);

	soldier->Physics.setInertia(0.0f, 0.0f, 0.0f);

	soldier->Physics.enablePhysics(0.0f, 0.0f, 0.0f);

	soldier->loadShaderProgram("vertexShader.glsl", "fragmentShader.glsl");

	gameObjectList.push_back(soldier);

	soldier = new GameObject();

	soldier->loadMeshes("basicCharacter.fbx");
	soldier->loadDiffuseMap("skin_woman.png");
	soldier->Transform.setPosition(glm::vec3(10.0f, 0.0f, 0.0f));
	soldier->Transform.setScale(glm::vec3(1.0f, 1.0f, 1.0f));

	soldier->Transform.update();

	soldier->Physics.setCollisionBoxSize(0.5f, 1.0f, 0.5f);

	soldier->Physics.setMass(0.0f);

	soldier->Physics.setInertia(0.0f, 0.0f, 0.0f);

	soldier->Physics.enablePhysics(10.0f, 0.0f, 0.0f);

	soldier->loadShaderProgram("lightVertexShader.glsl", "lightFragmentShader.glsl");

	gameObjectList.push_back(soldier);

	soldier = new GameObject();

	soldier->loadMeshes("basicCharacter.fbx");
	soldier->loadDiffuseMap("skin_man.png");
	soldier->Transform.setPosition(glm::vec3(-10.0f, 0.0f, 0.0f));
	soldier->Transform.setScale(glm::vec3(1.0f, 1.0f, 1.0f));

	soldier->Transform.update();

	soldier->Physics.setCollisionBoxSize(0.5f, 1.0f, 0.5f);

	soldier->Physics.setMass(1.0f);

	soldier->Physics.setInertia(0.0f, 0.0f, 0.0f);

	soldier->Physics.enablePhysics(-10.0f, 0.0f, 0.0f);

	soldier->loadShaderProgram("vertexShader.glsl", "fragmentShader.glsl");

	gameObjectList.push_back(soldier);

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

	int lastTicks = SDL_GetTicks();
	int currentTicks = SDL_GetTicks();

	//Colour Buffer Texture
	GLuint ColourBufferID = createTexture(800, 600);

	//Create Depth Buffer
	GLuint depthRenderBufferID;
	glGenRenderbuffers(1, &depthRenderBufferID);
	glBindRenderbuffer(GL_RENDERBUFFER, depthRenderBufferID);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, 800, 600);

	//Create Frame Buffer
	GLuint FrameBufferID;
	glGenFramebuffers(1, &FrameBufferID);
	glBindFramebuffer(GL_FRAMEBUFFER, FrameBufferID);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthRenderBufferID);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, ColourBufferID, 0);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Unable to create frame buffer for post processing", "frame Buffer error", NULL);
	}

	//Create Quad
	GLfloat screenVertices[] =
	{
		-1, -1,
		 1, -1,
		-1,  1,
		 1,  1
	};

	GLuint screenQuadVBOID;
	glGenBuffers(1, &screenQuadVBOID);
	glBindBuffer(GL_ARRAY_BUFFER, screenQuadVBOID);
	glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(GLfloat), screenVertices, GL_STATIC_DRAW);

	GLuint screenVAO;
	glGenVertexArrays(1, &screenVAO);
	glBindVertexArray(screenVAO);
	glBindBuffer(GL_ARRAY_BUFFER, screenQuadVBOID);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, NULL);


	GLuint postProcessingProgramID = LoadShaders("passThroughVertexShader.glsl", "postColourEnhancement.glsl");
	GLint texture0Location = glGetUniformLocation(postProcessingProgramID, "texture0");

	btDefaultCollisionConfiguration* collisionConfiguration = new btDefaultCollisionConfiguration();

	btCollisionDispatcher* dispatcher = new btCollisionDispatcher(collisionConfiguration);

	btBroadphaseInterface* overlappingPairCache = new btDbvtBroadphase();

	btSequentialImpulseConstraintSolver * solver = new btSequentialImpulseConstraintSolver;

	btDiscreteDynamicsWorld* dynamicWorld = new btDiscreteDynamicsWorld(dispatcher, overlappingPairCache, solver, collisionConfiguration);

	dynamicWorld->setGravity(btVector3(0, -10, 0));

	btCollisionShape* groundShape = new btBoxShape(btVector3(btScalar(50.), btScalar(2.), btScalar(50.)));

	btTransform groundTransform;
	groundTransform.setIdentity();
	groundTransform.setOrigin(btVector3(0, -10, 0));

	btScalar mass(0.);
	btVector3 localInertia(0, 0, 0);

	btDefaultMotionState* myMotionState = new btDefaultMotionState(groundTransform);
	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, groundShape, localInertia);
	btRigidBody* ground = new btRigidBody(rbInfo);

	dynamicWorld->addRigidBody(ground);

	for (GameObject * pCurrentObj : gameObjectList)
	{
		dynamicWorld->addRigidBody(pCurrentObj->Physics.getRigidBody());
	}

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

				case SDLK_1:
					postProcessingOn = false;
					break;

				case SDLK_2:
					postProcessingOn = true;
					break;

				case SDLK_3:
					physicsActive = true;
					break;
				}
			}
		}

		SDL_GetRelativeMouseState(&mouseXPosition, &mouseYPosition);



		currentTicks = SDL_GetTicks();
		float deltaTime = (float)(currentTicks - lastTicks) / 1000.0f;
		
		if (physicsActive == true) 
		{
			dynamicWorld->stepSimulation(1.f / 60.0f, 10);
		}

		if (mouseXPosition != 0 && mouseYPosition != 0)
		{
			horizontalAngle += mouseSpeed * deltaTime * float(mouseXPosition);
			verticalAngle += mouseSpeed * deltaTime * float(mouseYPosition);

			sceneCamera->rotate(float(mouseXPosition), float(mouseYPosition));
		}
		//Update Screenspace
		glEnable(GL_DEPTH_TEST);
		glBindFramebuffer(GL_FRAMEBUFFER, FrameBufferID);
		glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
		glClearDepth(1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



		viewMatrix = sceneCamera->cameraMatrix;

		for (GameObject * pCurrentObj : gameObjectList)
		{

			vec3 CameraPosition = sceneCamera->getworldPosition();

			if (physicsActive == true)
			{
				pCurrentObj->Physics.updatePhysics();
			}
			pCurrentObj->Transform.update();

			mat4 MVPMatrix = projectionMatrix * viewMatrix * pCurrentObj->Transform.getModelMatrix();

			pCurrentObj->preRender();
			
			pCurrentObj->Lighting.sendLightingData();

			GLuint cameraPositionLocation = glGetUniformLocation(pCurrentObj->getShaderProgramID(), "cameraPosition");

			glUniform3fv(cameraPositionLocation, 1, value_ptr(CameraPosition));

			GLint modelMatrixLocation = glGetUniformLocation(pCurrentObj->getShaderProgramID(), "modelMatrix");

			mat4 ModelMatrix = pCurrentObj->Transform.getModelMatrix();

			glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, &ModelMatrix[0][0]);

			GLint MVPMatrixLocation = glGetUniformLocation(pCurrentObj->getShaderProgramID(), "MVPMatrix");

			glUniformMatrix4fv(MVPMatrixLocation, 1, GL_FALSE, &MVPMatrix[0][0]);

			pCurrentObj->render();
		}

		glDisable(GL_DEPTH_TEST);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glClearColor(0.0f, 0.3f, 0.3f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		if (postProcessingOn == true)
		{
			glUseProgram(postProcessingProgramID);


			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, ColourBufferID);

			glUniform1i(texture0Location, 0);

			glBindVertexArray(screenVAO);
			glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		}
		SDL_GL_SwapWindow(window);

		lastTicks = currentTicks;
	}

	//code snippet from Bullet Physics
	for (int iterator = dynamicWorld->getNumCollisionObjects() - 1; iterator >= 0; iterator--)
	{
		btCollisionObject* obj = dynamicWorld->getCollisionObjectArray()[iterator];
		btRigidBody* body = btRigidBody::upcast(obj);
		if (body && body->getMotionState())
		{
			delete body->getMotionState();
		}
		dynamicWorld->removeCollisionObject(obj);
		delete obj;
	}

	delete sceneCamera;

	delete dynamicWorld;

	delete solver;

	delete overlappingPairCache;

	delete dispatcher;

	delete collisionConfiguration;


	glDeleteProgram(postProcessingProgramID);
	glDeleteVertexArrays(1, &screenVAO);
	glDeleteBuffers(1, &screenQuadVBOID);
	glDeleteFramebuffers(1, &FrameBufferID);
	glDeleteRenderbuffers(1, &depthRenderBufferID);
	glDeleteTextures(1, &ColourBufferID);

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
	return 0;
}

int initGLEW()
{
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
