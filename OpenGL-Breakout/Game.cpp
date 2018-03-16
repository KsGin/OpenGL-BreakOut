#include "Game.h"
#include "ResourceManager.h"
#include "SpriteRender.h"
#include "Texture2D.h"
#include <Glm/gtc/matrix_transform.inl>
#include <GLFW/glfw3.h>
#include <chrono>
#include <thread>

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

	keys = std::vector<GLboolean>(1024, GL_FALSE);

	// 加载着色器
	ResourceManager::LoadShader("resources/shaders/sprite.vertexShader", "resources/shaders/sprite.fragmentShader", nullptr, "sprite");
	// 配置着色器
	const auto projection = glm::ortho(0.0f, static_cast<GLfloat>(this->width),
		static_cast<GLfloat>(this->height), 0.0f, -1.0f, 1.0f);
	ResourceManager::GetShader("sprite").Use().SetInteger("sprite", 0);
	ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);
	// 设置专用于渲染的控制
	renderer = new SpriteRenderer(ResourceManager::GetShader("sprite"));
	// 加载纹理
	ResourceManager::LoadTexture2D("resources/textures/awesomeface.png", GL_TRUE, "face");
	ResourceManager::LoadTexture2D("resources/textures/background.jpg", GL_FALSE, "background");
	ResourceManager::LoadTexture2D("resources/textures/block.png", GL_FALSE, "block");
	ResourceManager::LoadTexture2D("resources/textures/block_solid.png", GL_FALSE, "block_solid");
	ResourceManager::LoadTexture2D("resources/textures/paddle.png", GL_TRUE, "paddle");
	// 加载关卡
	GameLevel one;
	one.Load("resources/levels/one.lvl", this->width, this->height * 0.5);
	GameLevel two;
	two.Load("levels/two.lvl", this->width, this->height * 0.5);
	GameLevel three;
	three.Load("levels/three.lvl", this->width, this->height * 0.5);
	GameLevel four;
	four.Load("levels/four.lvl", this->width, this->height * 0.5);
	this->levels.push_back(one);
	this->levels.push_back(two);
	this->levels.push_back(three);
	this->levels.push_back(four);
	this->level = 0;

	// 加载挡板
	const auto paddleSize = glm::vec2(200.0f, 40.0f);
	const auto paddlePos = glm::vec2(static_cast<GLfloat>(width) / 2 - paddleSize.x / 2, height - paddleSize.y / 2);	//在底部
	player = GameObject(paddlePos, paddleSize, ResourceManager::GetTexture2D("paddle"), glm::vec3(0.3f), glm::vec2(500.0f));

	// 加载弹性球 
	const auto ballRadius = 12.5f;
	const auto ballPos = paddlePos + glm::vec2(player.size.x / 2 - ballRadius, -player.size.y + ballRadius);		//在挡板上面最中央
	ball = BallObject(ballPos, ballRadius, glm::vec2(100.0f, -100.0f), ResourceManager::GetTexture2D("face"));
}

/**
 * 处理输入
 */
void Game::ProcessInput(const GLuint dt) {
	if (this->state == GAME_ACTIVE)
	{
		const auto velocity = 10.0f * dt;
		// 移动挡板
		if (this->keys[GLFW_KEY_A])
		{
			if (player.position.x >= 0) {
				player.position.x -= velocity;
				if (ball.stuck) {
					ball.position.x -= velocity;
				}
			}

		}
		if (this->keys[GLFW_KEY_D])
		{
			if (player.position.x <= this->width - player.size.x) {
				player.position.x += velocity;
				if (ball.stuck) {
					ball.position.x += velocity;
				}
			}
		}
		if (this->keys[GLFW_KEY_SPACE])
		{
			ball.stuck = !ball.stuck;
		}
	}
}

/**
 * 更新游戏状态
 */ 
void Game::Update(const GLfloat dt) {
	if (this->state == GAME_ACTIVE) {
		ball.Move(dt, width);
	}
}

/**
 * 渲染游戏
 */
void Game::Render() {
	if (this->state == GAME_ACTIVE)
	{
		// 绘制背景
		auto backgroundTexture = ResourceManager::GetTexture2D("background");
		renderer->DrawSprite(backgroundTexture, glm::vec2(0, 0), glm::vec2(this->width, this->height), 0.0f);
		// 绘制关卡
		this->levels[this->level].Draw(*renderer);
		// 绘制挡板
		this->player.Draw(*renderer);
		// 绘制球
		this->ball.Draw(*renderer);
	}
}
