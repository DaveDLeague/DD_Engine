#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "Texture.h"
#include "SpriteRenderer.h"


class GameObject
{
public:
    glm::vec2 position; 
	glm::vec2 size;
	glm::vec2 velocity;
    glm::vec3 color;
    GLfloat rotation;
	Texture2D   sprite;
    GLboolean isSolid;
    GLboolean destroyed;

    GameObject();
    GameObject(glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec3 color = glm::vec3(1.0f), glm::vec2 velocity = glm::vec2(0.0f, 0.0f));

    virtual void draw(SpriteRenderer &renderer);
};
