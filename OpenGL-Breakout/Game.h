#pragma once
#include <GL/glew.h>
#include "SpriteRender.h"
#include "GameLevel.h"
#include "BallObject.h"
#include "ParticleGeneraltor.h"

enum GameState {
	GAME_ACTIVE,
	GAME_MENU,
	GAME_WIN,
	GAME_READY
};

enum Direction {
	RIGHT,
	DOWN,
	LEFT,
	UP,
	CORNER_N,
	CORNER_E
};

class Game {
public:

	typedef std::tuple<GLboolean, Direction, glm::vec2> Collision; 

	SpriteRenderer *renderer;

	GameState state = GAME_READY;
	std::vector<GLboolean> keys;
	GLuint width, height;

	std::vector<GameLevel> levels;
	GLuint                 level{};

	GameObject      player;
	BallObject		ball;

	ParticleGenerator   particles; 

	Game(GLuint width, GLuint height);
	~Game();

	bool CollisionDetection(const GameObject &brick, BallObject &ball, int& xy) const;

	void Init();
	void ProcessInput(GLuint dt);
	void Update(GLfloat dt);
	void Render();
};

