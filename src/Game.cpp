#include "Game.h"
#include "ResourceManager.h"
#include "SpriteRenderer.h"

SpriteRenderer* renderer;

const glm::vec2 PLAYER_SIZE(100, 20);
const GLfloat PLAYER_VELOCITY(500.0f);

GameObject *player;

Game::Game(GLuint width, GLuint height) 
	: currentState(GAME_RUNNING), keys(), width(width), height(height){ 

}

Game::~Game(){
	delete renderer;
}

void Game::init(){
	ResourceManager::loadTexture("textures/awesomeface.png", GL_TRUE, "face");
	ResourceManager::loadTexture("textures/block.png", GL_FALSE, "block");
    ResourceManager::loadTexture("textures/block_solid.png", GL_FALSE, "block_solid");	
 	ResourceManager::loadTexture("textures/paddle.png", true, "paddle");
	
	glm::vec2 playerPos = glm::vec2(
        this->width / 2 - PLAYER_SIZE.x / 2, 
        this->height - PLAYER_SIZE.y
    );
    player = new GameObject(playerPos, PLAYER_SIZE, ResourceManager::getTexture("paddle"));

	GameLevel one; 
	one.load("levels/level1.lvl", this->width, this->height * 0.5);
    GameLevel two; 
	two.load("levels/level2.lvl", this->width, this->height * 0.5);
	
    this->levels.push_back(one);
    this->levels.push_back(two);
    this->level = 1;		

	ResourceManager::loadShader("shaders/vertex.vs", "shaders/fragment.fs", NULL, "sprite");
	ResourceManager::getShader("sprite").use();
    glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(this->width), static_cast<GLfloat>(this->height), 0.0f, -1.0f, 1.0f);

    ResourceManager::getShader("sprite").setMatrix4("projection", projection);

    renderer = new SpriteRenderer(ResourceManager::getShader("sprite"));
}

void Game::update(GLfloat dt){

}


void Game::processInput(GLfloat dt){
	const Uint8* keys = SDL_GetKeyboardState(NULL);

	if (this->currentState == GAME_RUNNING)
    {
        GLfloat velocity = PLAYER_VELOCITY * dt;
        
        if (keys[SDL_SCANCODE_A])
        {
            if (player->position.x >= 0)
                player->position.x -= velocity;
        }
        if (keys[SDL_SCANCODE_D])
        {
            if (player->position.x <= this->width - player->size.x)
                player->position.x += velocity;
        }
    }
	
}

void Game::render(){
	if(this->currentState == GAME_RUNNING)
    {
        renderer->drawSprite(ResourceManager::getTexture("face"), 
            glm::vec2(0, 0), glm::vec2(this->width, this->height), 0.0f
        );

        this->levels[this->level].draw(*renderer);
		player->draw(*renderer);
    }
}
