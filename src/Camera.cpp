#include "Camera.h"
#include <stdio.h>
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

void Camera::update(float deltaTime){
	this->front.x = cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
    this->front.y = sin(glm::radians(this->pitch));
    this->front.z = sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
    this->front = glm::normalize(front);
    this->right = glm::normalize(glm::cross(this->front, this->globalUp));  
    this->up = glm::normalize(glm::cross(this->right, this->front));
}
