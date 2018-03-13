#include "Game.h"
#include "ResourceManager.h"
#include "SpriteRender.h"
#include "Texture2D.h"
#include <Glm/gtc/matrix_transform.inl>

/**
 * Game 类构造方法
 */
Game::Game(const GLuint width, const GLuint height) : width(width), height(height) {
	this->Init();
}

/**
 * Game 类析构函数
 */
Game::~Game() {
}

/**
 * 初始化方法
 */
void Game::Init() {
	// 加载着色器
	ResourceManager::LoadShader("resources/shaders/sprite.vertexShader", "resources/shaders/sprite.fragmentShader", nullptr, "sprite");
	// 配置着色器
	const auto projection = glm::ortho(0.0f, static_cast<GLfloat>(this->width),
		static_cast<GLfloat>(this->height), 0.0f, -1.0f, 1.0f);
	ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);
	ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);
	// 设置专用于渲染的控制
	renderer = new SpriteRenderer(ResourceManager::GetShader("sprite"));
	// 加载纹理
	ResourceManager::LoadTexture2D("resources/textures/awesomeface.png", GL_TRUE, "face");

}

/**
 * 处理输入
 */
void Game::ProcessInput(GLuint dt) {
}

/**
 * 更新游戏状态
 */
void Game::Update(GLfloat dt) {
}

/**
 * 渲染游戏
 */
void Game::Render() const {
	auto spriteTexture = ResourceManager::GetTexture2D("face");
	renderer->DrawSprite(spriteTexture, glm::vec2(100.0f, 100.0f), glm::vec2(200, 300), 45.0f,
		glm::vec3(0.1f, 0.1f, 0.1f));
}
