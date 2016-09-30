#pragma once

#include "GL/glew.h"
#include "SDL2/SDL.h"

enum GameState{
	GAME_RUNNING,
	GAME_MENU,
	GAME_OVER
};

class Game{

public:
	GameState currentState;
	GLboolean keys[1024];
	GLuint width;
	GLuint height;


	Game(GLuint width, GLuint height);
	~Game();

	void init();

	void processInput(GLfloat dt);
	void update(GLfloat dt);
	void render();
};

