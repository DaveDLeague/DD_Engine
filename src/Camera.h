#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "SDL2/SDL.h"

class Camera{
public:
	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 globalUp;

	float yaw;
	float pitch;
	float roll;
		
	Camera();
	~Camera();

	void update(float deltaTime);
	inline void setWindowID(int id){ windowID = id; win = SDL_GetWindowFromID(windowID);}
private:
	int windowID;

	SDL_Window* win;
};
