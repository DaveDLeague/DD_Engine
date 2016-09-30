#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

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
private:
};
