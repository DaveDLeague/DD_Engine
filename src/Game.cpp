#include "Game.h"
#include "ResourceManager.h"
#include "Renderer3D.h"
#include "SpriteRenderer.h"
#include "TextRenderer.h"

#include <sstream>

const float CAMERA_SPEED = 1.0f;

std::stringstream ss;

Renderer3D* renderer;
SpriteRenderer* spriteRenderer;
TextRenderer* textRenderer;

Model tri;

Game::Game(GLuint width, GLuint height) 
	: currentState(GAME_RUNNING), keys(), width(width), height(height){ 

}

Game::~Game(){
	delete renderer;
	delete spriteRenderer;
	delete textRenderer;
}

void Game::init(){
	GLuint VBO;

	ResourceManager::loadShader("shaders/shader3d.vs", "shaders/shader3d.fs", NULL, "shader3D"); 
	renderer = new Renderer3D(ResourceManager::getShader("shader3D"));

	ResourceManager::loadShader("shaders/vertex.vs", "shaders/fragment.fs", NULL, "sprite");
	spriteRenderer = new SpriteRenderer(ResourceManager::getShader("sprite"));
	
	ResourceManager::loadShader("shaders/text_vertex.vs", "shaders/text_fragment.fs", NULL, "text");
	textRenderer = new TextRenderer(ResourceManager::getShader("text"));
	textRenderer->setDimensions(width, height);	

	ResourceManager::loadTexture("textures/block.png", false, "block");
	ResourceManager::getShader("sprite").use();
	glm::mat4 proj = glm::ortho(0.0f, static_cast<GLfloat>(this->width), static_cast<GLfloat>(this->height), 0.0f, -1.0f, 1.0f);
	ResourceManager::getShader("sprite").setMatrix4("projection", proj);

	GLfloat vertices[] = {
		0.0f, 0.0f, 0.0f,
        0.5f, 1.0f, 0.0f,
        1.0f, 0.0f, 0.0f
    };

    glGenVertexArrays(1, &tri.vao);
    glGenBuffers(1, &VBO);

	glBindVertexArray(tri.vao);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindVertexArray(0); 

	tri.position = glm::vec3(0.0f, 0.0f, -3.0f);
	tri.scale = glm::vec3(1.0, 1.0f, 1.0f);
	
	renderer->setProjection(glm::perspective(glm::radians(45.0f), static_cast<float>(this->width / this->height), 0.1f, 1000.0f));
}
float f = 0.0f;
void Game::update(GLfloat dt){
	camera.update(dt);
}

void Game::processInput(GLfloat dt){
	const Uint8* keys = SDL_GetKeyboardState(NULL);

	if(keys[SDL_SCANCODE_W]){
		camera.position += camera.front * CAMERA_SPEED * dt;
	}
	if(keys[SDL_SCANCODE_S]){
		camera.position += -camera.front * CAMERA_SPEED * dt;
	}
	if(keys[SDL_SCANCODE_A]){
		camera.position -= camera.right * CAMERA_SPEED * dt;
	}
	if(keys[SDL_SCANCODE_D]){
		camera.position += camera.right * CAMERA_SPEED * dt;
	}
	if(keys[SDL_SCANCODE_R]){
		camera.position += camera.up * CAMERA_SPEED * dt;
	}
	if(keys[SDL_SCANCODE_F]){
		camera.position -= camera.up * CAMERA_SPEED * dt;
	}
	if(keys[SDL_SCANCODE_LEFT]){
		camera.yaw -= 30.0f * dt;
	}
	if(keys[SDL_SCANCODE_RIGHT]){
		camera.yaw += 30.0f * dt;
	}
	if(keys[SDL_SCANCODE_UP]){
		camera.pitch += 30.0f * dt;
	}
	if(keys[SDL_SCANCODE_DOWN]){
		camera.pitch -= 30.0f * dt;
	}
}

void Game::render(){
	renderer->drawModel(tri, camera);
	spriteRenderer->drawSprite(ResourceManager::getTexture("block"), glm::vec2(0, 0), glm::vec2(200.0f, 150.0f), 0.0f);
	ss << "camera x:" << camera.position.x << " y:" << camera.position.y << " z:" << camera.position.z;
	textRenderer->renderText(ss.str(), 1.0f, 600.0f, 0.3f, glm::vec3(1.0f, 0.0f, 0.0f));
	ss.str("");
	ss << "camera pitch:" << camera.pitch << " roll:" << camera.roll << " yaw:" << camera.yaw;
	textRenderer->renderText(ss.str(), 1.0f, 550.0f, 0.3f, glm::vec3(1.0f, 0.0f, 0.0f));
	ss.str("");
}
