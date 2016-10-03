#pragma once

#include <string>
#include <map>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"

struct Character {
    GLuint TextureID;
    glm::ivec2 Size;   
    glm::ivec2 Bearing; 
    long Advance;   
};

class TextRenderer{
public:
	TextRenderer(Shader shader);
	~TextRenderer();

	void renderText(std::string text, int x, int y, float size, glm::vec3 color);
	void setDimensions(float w, float h);
	void loadFont(std::string fontName, std::string fontLoc);
	void setFont(std::string);
		
private:
    GLuint VAO;
	GLuint VBO;
	GLuint colorUniLoc;

	std::string currentFont;

	std::map<GLchar, Character> characters;
	std::map<std::string, std::map<GLchar, Character> > fonts;

	Shader shader;

	void initBuffer();
};
