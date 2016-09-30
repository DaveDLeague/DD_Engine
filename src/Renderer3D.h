#pragma once

#include "GL/glew.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "Texture.h"
#include "Shader.h"
#include "Camera.h"

struct Model{
	GLuint vao;
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;
};

class Renderer3D
{
public:	
    Renderer3D(Shader shader);
    ~Renderer3D();

    void drawModel(Model& m, Camera c);

	void setProjection(glm::mat4 p){ projection = p; } 

private:
    void initRenderData();
	Shader shader;

	glm::mat4 projection;
};
