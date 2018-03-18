#include "Game.h"
#include "ResourceManager.h"
#include "SpriteRender.h"
#include "Texture2D.h"
#include <Glm/gtc/matrix_transform.inl>
#include <GLFW/glfw3.h>
#include <iostream>

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

bool Game::CollisionDetection(const GameObject& brick, const BallObject& ball, int& xy) const {
	// ����κ�Բ�е�����
	const glm::vec2 brickCenterPos = brick.position + glm::vec2(brick.size.x / 2.0, brick.size.y / 2.0);
	const glm::vec2 ballCenterPos = ball.position + glm::vec2(ball.radius / 2.0);

	// ��ʸ��
	const glm::vec2 vecBrickToBall = ballCenterPos - brickCenterPos;

	// ����ʸ�����������
	const glm::vec2 vec = glm::vec2(
		glm::max(glm::min(brick.size.x / 2, vecBrickToBall.x), -brick.size.x / 2),
		glm::max(glm::min(brick.size.y / 2, vecBrickToBall.y), -brick.size.y / 2)
	);
	const glm::vec2 pos = brickCenterPos + vec;

	if (glm::distance(pos, ballCenterPos) <= ball.radius) {
		// �ж������ķ���
		std::vector<glm::vec2> compess{
			glm::vec2(0.0f , -1.0f),
			glm::vec2(1.0f , 0.0f),
			glm::vec2(0.0f , 1.0f),
			glm::vec2(-1.0f , 0.0f),
			glm::normalize(glm::vec2(brick.size.x , -brick.size.y)), //����
			glm::normalize(glm::vec2(brick.size.x , brick.size.y)), //����
			glm::normalize(glm::vec2(-brick.size.x , brick.size.y)), //����
			glm::normalize(glm::vec2(-brick.size.x , -brick.size.y)), //����
		};

		std::vector<float> dots(0);
		for (int i = 0; i < 4; ++i) {
			dots.push_back(glm::dot(compess[i], glm::normalize(vecBrickToBall)));
		}

		const glm::vec2 velo = glm::normalize(ball.velocity);
		float f;
		if (dots[0] >= 0 && dots[0] <= 1 && dots[1] >= 0 && dots[1] <= 1) {
			f = glm::dot(compess[1], compess[4]);
			xy = dots[1] >= f ? 0 : 3;
			if (dots[1] == f && glm::dot(compess[4], velo) == -1) {
				xy = 4;
			}
		}
		if (dots[1] >= 0 && dots[1] <= 1 && dots[2] >= 0 && dots[2] <= 1) {
			f = glm::dot(compess[2], compess[5]);
			xy = (dots[2] >= f ? 1 : 0);
			if (dots[2] == f && glm::dot(compess[5], velo) == -1) {
				xy = 4;
			}
		}
		if (dots[2] >= 0 && dots[2] <= 1 && dots[3] >= 0 && dots[3] <= 1) {
			f = glm::dot(compess[3], compess[6]);
			xy = (dots[3] >= f ? 2 : 1);
			if (dots[3] == f && glm::dot(compess[6], velo) == -1) {
				xy = 4;
			}
		}
		if (dots[3] >= 0 && dots[3] <= 1 && dots[0] >= 0 && dots[0] <= 1) {
			f = glm::dot(compess[0], compess[7]);
			xy = (dots[0] >= f ? 3 : 2);
			if (dots[0] == f && glm::dot(compess[7], velo) == -1) {
				xy = 4;
			}
		}
		return true;
	}
	return false;
}

/**
 * ��ʼ������
 */
void Game::Init() {

	keys = std::vector<GLboolean>(1024, GL_FALSE);

	// ������ɫ��
	ResourceManager::LoadShader("resources/shaders/sprite.vertexShader", "resources/shaders/sprite.fragmentShader", nullptr, "sprite");
	ResourceManager::LoadShader("resources/shaders/particle.vertexShader", "resources/shaders/particle.fragmentShader", nullptr, "particle");
	// ������ɫ��
	const auto projection = glm::ortho(0.0f, static_cast<GLfloat>(this->width), static_cast<GLfloat>(this->height), 0.0f, -1.0f, 1.0f);
	ResourceManager::GetShader("sprite").Use().SetInteger("sprite", 0);
	ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);
	ResourceManager::GetShader("particle").Use().SetInteger("particle", 0);
	ResourceManager::GetShader("particle").SetMatrix4("projection", projection);
	// ����ר������Ⱦ�Ŀ���
	renderer = new SpriteRenderer(ResourceManager::GetShader("sprite"));
	particles = ParticleGenerator(ResourceManager::GetShader("particle"), ResourceManager::GetTexture2D("face"), 500);
	// ��������
	ResourceManager::LoadTexture2D("resources/textures/awesomeface.png", GL_TRUE, "face");
	ResourceManager::LoadTexture2D("resources/textures/background.jpg", GL_FALSE, "background");
	ResourceManager::LoadTexture2D("resources/textures/block.png", GL_FALSE, "block");
	ResourceManager::LoadTexture2D("resources/textures/block_solid.png", GL_FALSE, "block_solid");
	ResourceManager::LoadTexture2D("resources/textures/paddle.png", GL_TRUE, "paddle");
	// ���عؿ�
	GameLevel one;
	one.Load("resources/levels/one.lvl", this->width, this->height * 0.4);
	GameLevel two;
	two.Load("levels/two.lvl", this->width, this->height * 0.4);
	GameLevel three;
	three.Load("levels/three.lvl", this->width, this->height * 0.4);
	GameLevel four;
	four.Load("levels/four.lvl", this->width, this->height * 0.4);
	this->levels.push_back(one);
	this->levels.push_back(two);
	this->levels.push_back(three);
	this->levels.push_back(four);
	this->level = 0;

	// ���ص���
	const auto paddleSize = glm::vec2(200.0f, 40.0f);
	const auto paddlePos = glm::vec2(static_cast<GLfloat>(width) / 2 - paddleSize.x / 2, height - paddleSize.y / 2);	//�ڵײ�
	player = GameObject(paddlePos, paddleSize, ResourceManager::GetTexture2D("paddle"), glm::vec3(0.3f), glm::vec2(500.0f));

	// ���ص����� 
	const auto ballRadius = 12.5f;
	const auto ballPos = paddlePos + glm::vec2(player.size.x / 2 - ballRadius, -player.size.y + ballRadius);		//�ڵ�������������
	ball = BallObject(ballPos, ballRadius, glm::vec2(50.0f, -50.0f), ResourceManager::GetTexture2D("face"));
}

/**
 * ��������
 */
void Game::ProcessInput(const GLuint dt) {
	if (this->state == GAME_ACTIVE)
	{
		const auto velocity = 10.0f * dt;
		// �ƶ�����
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
		if (this->keys[GLFW_KEY_F1])
		{
			ball.stuck = false;
		}
		if (this->keys[GLFW_KEY_F2])
		{
			ball.stuck = true;
		}
	}
}

/**
 * ������Ϸ״̬
 */
void Game::Update(const GLfloat dt) {
	if (this->state == GAME_ACTIVE) {
		//particles.Update(dt, ball, 2 , glm::vec2(ball.radius / 2));
		ball.Move(dt, width);
		int xy = 0;
		for (GameObject& obj : levels[level].bricks) {
			if (!obj.destroyed && CollisionDetection(obj, ball, xy)) {
				if (!obj.isSolid) {
					obj.destroyed = true;
				}
				if (xy == UP || xy == DOWN) {
					ball.velocity.y = -ball.velocity.y;
				}
				else {
					ball.velocity.y = -ball.velocity.y;
				}
			}
		}
		if (CollisionDetection(player, ball, xy) && xy == UP) {
			ball.velocity.y = -ball.velocity.y;
		}
		if (ball.position.y >= height) {
			player.position = glm::vec2(static_cast<GLfloat>(width) / 2 - player.size.x / 2, height - player.size.y / 2);
			ball.Reset(player.position + glm::vec2(player.size.x / 2 - ball.radius, -player.size.y + ball.radius), glm::vec2(50.0f, -50.0f));
			for (auto& obj : levels[level].bricks) {
				obj.destroyed = false;
			}
		}
	}

	if (levels[level].IsCompleted()) {
		ball.Reset(player.position + glm::vec2(player.size.x / 2 - ball.radius, -player.size.y + ball.radius), glm::vec2(50.0f, -50.0f));
	}
}

/**
 * ��Ⱦ��Ϸ
 */
void Game::Render() {
	if (this->state == GAME_ACTIVE)
	{
		// ���Ʊ���
		auto backgroundTexture = ResourceManager::GetTexture2D("background");
		renderer->DrawSprite(backgroundTexture, glm::vec2(0, 0), glm::vec2(this->width, this->height), 0.0f);
		// ���ƹؿ�
		this->levels[this->level].Draw(*renderer);
		// ���Ƶ���
		this->player.Draw(*renderer);
		// ������
		this->ball.Draw(*renderer);

		//this->particles.Draw();
	}
}
