#pragma once
#include "GameObject.h"

class BallObject : public GameObject {
public:
	// ÇòµÄ×´Ì¬ 
	GLfloat   radius;
	GLboolean stuck;


	BallObject();
	BallObject(glm::vec2 pos, GLfloat radius, glm::vec2 velocity, Texture2D sprite);

	glm::vec2 Move(GLfloat dt, GLuint windowWidth);
	void      Reset(glm::vec2 position, glm::vec2 velocity);
};
