#pragma once

#include <vector>

#include "GL/glew.h"
#include "GameObject.h"

class GameLevel{
public:
	std::vector<GameObject> bricks;

    GameLevel() { }

    void load(const GLchar *file, GLuint levelWidth, GLuint levelHeight);
    void draw(SpriteRenderer &renderer);
    GLboolean isCompleted();

private:
	void init(std::vector<std::vector<GLuint> > tileData, GLuint levelWidth, GLuint levelHeight);
};
