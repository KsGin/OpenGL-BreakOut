#pragma once
#include <GL/glew.h>
#include "SpriteRender.h"
#include "GameLevel.h"
#include "BallObject.h"

enum GameState {
	GAME_ACTIVE,
	GAME_MENU,
	GAME_WIN
};


class Game {
public:

	SpriteRenderer  *renderer;

	GameState state;
	std::vector<GLboolean> keys;
	GLuint width, height;

	std::vector<GameLevel> levels;
    GLuint                 level;

	GameObject      player;
	BallObject		ball;

	Game(GLuint width , GLuint height);
	~Game();

	void Init();
	void ProcessInput(GLuint dt);
	void Update(GLfloat dt);
	void Render();
};

