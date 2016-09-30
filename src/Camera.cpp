#include "Camera.h"
#include <stdio.h>
#include <thread>

const float MOUSE_SENSITIVITY = 1.0f;

bool mouseLook = false;
bool clickLock = false;

Camera::Camera(){
	this->position = glm::vec3(0.0f, 0.0f, 0.0f);
	this->front = glm::vec3(0.0f, 0.0f, -1.0f); 
	this->up = glm::vec3(0.0f, 1.0f, 1.0f);
	this->right = glm::vec3(1.0f, 0.0f, 0.0f);
	this->globalUp = glm::vec3(0.0f, 1.0f, 0.0f);

	this->yaw = -90.0f;
	this->pitch = 0.0f;
	this->roll = 0.0f;
}

Camera::~Camera(){

}

void clamp(float &v, float l, float h){
	if(v > h){ v = h; }
	else if(v < 0){ v = 0; }
}

void Camera::update(float deltaTime){
	int mouseX;
	int mouseY;
	SDL_GetMouseState(&mouseX, &mouseY);
	
	int w;
	int h;
	SDL_GetWindowSize(win, &w, &h);
	w /= 2;
	h /= 2;

	if(SDL_BUTTON(SDL_BUTTON_LEFT)){
		SDL_ShowCursor(SDL_FALSE);
	}

	this->front.x = cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
    this->front.y = sin(glm::radians(this->pitch));
    this->front.z = sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
    this->front = glm::normalize(front);
    this->right = glm::normalize(glm::cross(this->front, this->globalUp));  
    this->up = glm::normalize(glm::cross(this->right, this->front));

	SDL_WarpMouseInWindow(SDL_GetWindowFromID(windowID), w, h);
	yaw += (mouseX - w) * MOUSE_SENSITIVITY * deltaTime;
	pitch -= (mouseY - h) * MOUSE_SENSITIVITY * deltaTime;	

	clamp(pitch, -90.0f, 90.0f);
	
}
