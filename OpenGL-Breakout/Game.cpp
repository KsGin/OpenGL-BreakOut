#include "Game.h"
#include "ResourceManager.h"
#include "SpriteRender.h"
#include "Texture2D.h"
#include <Glm/gtc/matrix_transform.inl>

/**
 * Game �๹�췽��
 */
Game::Game(const GLuint width, const GLuint height) : width(width), height(height) {
	this->Init();
}

/**
 * Game ����������
 */
Game::~Game() {
}

/**
 * ��ʼ������
 */
void Game::Init() {
	// ������ɫ��
	ResourceManager::LoadShader("resources/shaders/sprite.vertexShader", "resources/shaders/sprite.fragmentShader", nullptr, "sprite");
	// ������ɫ��
	const auto projection = glm::ortho(0.0f, static_cast<GLfloat>(this->width),
		static_cast<GLfloat>(this->height), 0.0f, -1.0f, 1.0f);
	ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);
	ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);
	// ����ר������Ⱦ�Ŀ���
	renderer = new SpriteRenderer(ResourceManager::GetShader("sprite"));
	// ��������
	ResourceManager::LoadTexture2D("resources/textures/awesomeface.png", GL_TRUE, "face");
	ResourceManager::LoadTexture2D("resources/textures/background.jpg", GL_FALSE, "background");
    ResourceManager::LoadTexture2D("resources/textures/awesomeface.png", GL_TRUE, "face");
    ResourceManager::LoadTexture2D("resources/textures/block.png", GL_FALSE, "block");
    ResourceManager::LoadTexture2D("resources/textures/block_solid.png", GL_FALSE, "block_solid");
    // ���عؿ�
    GameLevel one; 
	one.Load("resources/levels/one.lvl", this->width, this->height * 0.5);
//    GameLevel two; two.Load("levels/two.lvl", this->width, this->height * 0.5);
//    GameLevel three; three.Load("levels/three.lvl", this->width, this->height * 0.5);
//    GameLevel four; four.Load("levels/four.lvl", this->width, this->height * 0.5);
    this->levels.push_back(one);
//    this->levels.push_back(two);
//    this->levels.push_back(three);
//    this->levels.push_back(four);
    this->level = 1;


}

/**
 * ��������
 */
void Game::ProcessInput(GLuint dt) {
}

/**
 * ������Ϸ״̬
 */
void Game::Update(GLfloat dt) {
}

/**
 * ��Ⱦ��Ϸ
 */
void Game::Render() const {
	auto spriteTexture = ResourceManager::GetTexture2D("face");
	renderer->DrawSprite(spriteTexture, glm::vec2(100.0f, 100.0f), glm::vec2(200, 300), 45.0f,
		glm::vec3(0.1f, 0.2f, 0.1f));
}
