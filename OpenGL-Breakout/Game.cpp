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
		glm::vec3(0.1f, 0.1f, 0.1f));
}
