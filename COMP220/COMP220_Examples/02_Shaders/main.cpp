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

	if (IMG_Init(IMG_INIT_JPG| IMG_INIT_PNG) < 0)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, IMG_GetError(), "Image_Init failed", NULL);
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


	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);


	/*
	// An array of 3 vectors which represents 3 vertices
	static const GLfloat g_vertex_buffer_data[] = {
		//Front Panel
		-0.5f, 0.5f, 0.5f,
		0.5f, 0.5f, 0.5f,
		-0.5f, -0.5f, 0.5f,
		0.5f, -0.5f, 0.5f,
		0.5f, 0.5f, 0.5f,
		-0.5f, -0.5f, 0.5f,

		//Back Panel
		-0.5f, 0.5f, -0.5f,
		0.5f, 0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
		0.5f, 0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		
		//Top Panel
		-0.5f, 0.5f, 0.5f,
		0.5f, 0.5f, 0.5f,
		-0.5f, 0.5f, -0.5f,
		0.5f, 0.5f, -0.5f,
		0.5f, 0.5f, 0.5f,
		-0.5f, 0.5f, -0.5f,

		//Bottom Panel
		-0.5f, -0.5f, 0.5f,
		0.5f, -0.5f, 0.5f,
		-0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, 0.5f,
		-0.5f, -0.5f, -0.5f,

		//Left Hand Panel
		-0.5f, 0.5f, 0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f, 0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, 0.5f, -0.5f,
		-0.5f, -0.5f, 0.5f,

		//Right Hand Panel
		0.5f, 0.5f, 0.5f,
		0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, 0.5f,
		0.5f, -0.5f, -0.5f,
		0.5f, 0.5f, -0.5f,
		0.5f, -0.5f, 0.5f,


	};

	*/
	Vertex triangleVertices[]=
	{	
		//Back Panel
		{ -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f },
		{ 0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f},
		{ -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f},
		{ 0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f},
		{ 0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f},
		{ -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f },


		//Right Hand Panel
		{ 0.5f, 0.5f, 0.5f, 0.5f, 0.0f, 0.5f, 1.0f, 1.0f, 1.0f },
		{ 0.5f, -0.5f, -0.5f, 0.5f, 0.0f, 0.5f, 1.0f, 1.0f, 0.0f },
		{ 0.5f, -0.5f, 0.5f, 0.5f, 0.0f, 0.5f, 1.0f, 1.0f, 0.0f},
		{ 0.5f, -0.5f, -0.5f, 0.5f, 0.0f, 0.5f, 1.0f, 1.0f, 0.0f},
		{ 0.5f, 0.5f, -0.5f, 0.5f, 0.0f, 0.5f, 1.0f, 1.0f, 1.0f},
		{ 0.5f, -0.5f, 0.5f, 0.5f, 0.0f, 0.5f, 1.0f, 1.0f, 0.0f},
		
		//Bottom Panel
		{ -0.5f, -0.5f, 0.5f, 0.0f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f},
		{ 0.5f, -0.5f, 0.5f, 0.0f, 0.5f, 0.5f, 1.0f, 1.0f, 0.0f},
		{ -0.5f, -0.5f, -0.5f, 0.0f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f},
		{ 0.5f, -0.5f, -0.5f, 0.0f, 0.5f, 0.5f, 1.0f, 1.0f, 0.0f},
		{ 0.5f, -0.5f, 0.5f, 0.0f, 0.5f, 0.5f, 1.0f, 1.0f, 0.0f},
		{ -0.5f, -0.5f, -0.5f, 0.0f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f},

		//Left Hand Panel
		{ -0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f },
		{ -0.5f, -0.5f, -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f },
		{ -0.5f, -0.5f, 0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f },
		{ -0.5f, -0.5f, -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f },
		{ -0.5f, 0.5f, -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f },
		{ -0.5f, -0.5f, 0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f },
		
		//Top Panel
		{-0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f },
		{ 0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f },
		{ -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f },
		{ 0.5f, 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f },
		{ 0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f },
		{ -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f },

		//Front Panel
		{ -0.5f, 0.5f, 0.5f,1.0f,0.0f,0.0f,1.0f, 0.0f, 0.0f },
		{ 0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f },
		{ -0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f },
		{ 0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f },
		{ 0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f },
		{ -0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f }
	
	};

	unsigned int triangleIndecies[]=
	{
		0,1,2,
		3,4,5,
		6,7,8,
		9,10,11,
		12,13,14,
		15,16,17,
		18,19,20,
		21,22,23,
		24,25,26,
		27,28,29,
		30,31,32,
		33,34,35

	};

	// This will identify our vertex buffer
	GLuint vertexbuffer;
	// Generate 1 buffer, put the resulting identifier in vertexbuffer
	glGenBuffers(1, &vertexbuffer);
	// The following commands will talk about our 'vertexbuffer' buffer
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);

	glBufferData(GL_ARRAY_BUFFER, 36 * sizeof(Vertex), triangleVertices, GL_STATIC_DRAW);


	GLuint elementbuffer;
	glGenBuffers(1, &elementbuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 36 * sizeof(unsigned int), triangleIndecies, GL_STATIC_DRAW);

	GLuint textureID = loadTextureFromFile("DigCam.jpg");

	vec3 trianglePosition = vec3(0.0f, 0.0f, 0.0f);
	mat4 translationMatrix = translate(trianglePosition);
	vec3 triangleRotation = vec3(0.5f, 0.5f, 0.0f);

	mat4 rotationXMatrix = rotate(triangleRotation.x, vec3(1.0f, 0.0f, 0.0f));
	mat4 rotationYMatrix = rotate(triangleRotation.y, vec3(0.0f, 1.0f, 0.0f));
	mat4 rotationZMatrix = rotate(triangleRotation.z, vec3(0.0f, 0.0f, 1.0f));
	mat4 rotationMatrix = rotationZMatrix*rotationYMatrix*rotationXMatrix;

	mat4 modelMatrix = translationMatrix*rotationMatrix;

	vec3 cameraPosition = vec3(0.0f, 0.0f, 0.0f);
	vec3 cameraTarget = vec3(0.0f, 0.0f, 0.0f);
	vec3 cameraUP = vec3(0.0f, 0.0f, 0.0f);

	mat4 viewMatrix = lookAt(cameraPosition, cameraTarget, cameraUP);

	mat4 projectionMatrix = perspective(radians(90.0f), float(800 / 600), 0.1f, 100.0f);
	// Give our vertices to OpenGL.
	//glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	glBufferData(GL_ARRAY_BUFFER, sizeof(triangleVertices), triangleVertices, GL_STATIC_DRAW);


	GLuint programID = LoadShaders("TextureVertex.glsl", "TextureFrag.glsl");

	if (programID < 0)
	{
		
	}

	GLuint timelocation=glGetUniformLocation(programID, "time");

	GLint modelMatrixLocation = glGetUniformLocation(programID, "modelMatrix");
	GLint viewMatrixLocation = glGetUniformLocation(programID, "viewMatrix");
	GLint projectionMatrixLocation = glGetUniformLocation(programID, "projectionMatrix");
	GLint textureLocation = glGetUniformLocation(programID, "baseTexture");

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
				}
			}
		}

		float currentTicks = SDL_GetTicks();

		glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textureID);

		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);

		glUseProgram(programID);

		glUniform1f(timelocation, (float)(currentTicks / 1000.0f));

		glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, value_ptr(modelMatrix));
		glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, value_ptr(viewMatrix));
		glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, value_ptr(projectionMatrix));
		glUniform1i(textureLocation, 0);
	

		// 1rst attribute buffer : vertices
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(
			0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			sizeof(Vertex),                  // stride
			(void*)0            // array buffer offset
		);

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 4, GL_FLOAT,GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(float)));

		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(7*sizeof(float)));

		// Draw the triangle !
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (void*)0); // Starting from vertex 0; 3 vertices total -> 1 triangle
		
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);


		SDL_GL_SwapWindow(window);
	}

	glDeleteVertexArrays(1, &VertexArrayID);
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteBuffers(1, &elementbuffer);
	glDeleteTextures(1, &textureID);
	glDeleteProgram(programID);


	SDL_GL_DeleteContext(GL_Context);
	//Destroy the window and quit SDL2, NB we should do this after all cleanup in this order!!!
	//https://wiki.libsdl.org/SDL_DestroyWindow
	SDL_DestroyWindow(window);
	
	IMG_Quit();
	//https://wiki.libsdl.org/SDL_Quit
	
	SDL_Quit();

	return 0;
}