#include "GL/glew.h"
#include "SDL2/SDL.h"

#include "Game.h"
#include "ResourceManager.h"

const int SCREEN_WIDTH = 900; 
const int SCREEN_HEIGHT = 700;

void handleInput(SDL_Event *event);

bool quit = false;

Game game3d(SCREEN_WIDTH, SCREEN_HEIGHT);

int main(){
	SDL_Init(SDL_INIT_VIDEO);

	SDL_Window* window = SDL_CreateWindow("DD_ENGINE", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
	SDL_GLContext context = SDL_GL_CreateContext(window);   

	if(context == NULL){
		printf("Error creating OpenGL context.\n%s\n", SDL_GetError());
	}

    glewExperimental = GL_TRUE;
    glewInit();
	glGetError();

	game3d.init();

	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);	

	GLfloat deltaTime = 0.0f;
    GLfloat lastFrame = 0.0f;

	SDL_Event event;
	while(!quit){

		GLfloat currentFrame = SDL_GetTicks();
        deltaTime = (currentFrame - lastFrame) / 1000.0f;
        lastFrame = currentFrame;

        while(SDL_PollEvent(&event) != 0)
        {
			switch(event.type){
				case SDL_QUIT:{
					quit = true;
					break;
				}
				case SDL_KEYDOWN:
				case SDL_KEYUP:{
					handleInput(&event);
					break;
				}
			}
        }

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

		game3d.processInput(deltaTime);				
		game3d.update(deltaTime);
		game3d.render();

		SDL_GL_SwapWindow(window);
    }
	
	SDL_Quit();
}

void handleInput(SDL_Event *event){
	switch(event->key.keysym.sym){
		case SDLK_ESCAPE:{
			quit = true;
		}
	}
}

