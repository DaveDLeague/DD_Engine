#include <time.h>

#include "GL/glew.h"
#include "SDL2/SDL.h"

#include "Game.h"
#include "ResourceManager.h"


void handleInput(SDL_Event *event);

const GLuint SCREEN_WIDTH = 800;
const GLuint SCREEN_HEIGHT = 600;

Game breakout(SCREEN_WIDTH, SCREEN_HEIGHT);

bool quit = false;

int main(){
	
	SDL_Init(SDL_INIT_VIDEO);

	SDL_Window* window = SDL_CreateWindow("Breakout", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
	SDL_GLContext context = SDL_GL_CreateContext(window);   

	if(context == NULL){
		printf("Error creating OpenGL context.\n%s\n", SDL_GetError());
	}

    glewExperimental = GL_TRUE;
    glewInit();
	glGetError();

	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);	

	breakout.init();

	GLfloat deltaTime = 0.0f;
    GLfloat lastFrame = 0.0f;

	breakout.currentState = GAME_RUNNING;

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

		breakout.processInput(deltaTime);
		breakout.update(deltaTime);

		glClearColor(0.3f, 0.3f, 0.8f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        breakout.render();

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

