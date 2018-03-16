#include "BallObject.h"

BallObject::BallObject(): radius(0), stuck(true) {
}

BallObject::BallObject(const glm::vec2 pos, const GLfloat radius, const glm::vec2 velocity, const Texture2D sprite) {
	this->position = pos;
	this->velocity = velocity;
	this->sprite = sprite;
	this->radius = radius;
	this->stuck = true;
	this->size = glm::vec2(radius * 2, radius * 2);
	this->color = glm::vec3(0.2f);
}

glm::vec2 BallObject::Move(const GLfloat dt, const GLuint windowWidth) {
	    // ���û�б��̶��ڵ�����
    if (!this->stuck)
    { 
        // �ƶ���
        this->position += this->velocity * dt;
        // ����Ƿ��ڴ��ڱ߽����⣬����ǵĻ���ת�ٶȲ��ָ�����ȷ��λ��
        if (this->position.x <= 0.0f)
        {
            this->velocity.x = -this->velocity.x;
            this->position.x = 0.0f;
        }
        else if (this->position.x + this->size.x >= windowWidth)
        {
            this->velocity.x = -this->velocity.x;
            this->position.x = windowWidth - this->size.x;
        }
        if (this->position.y <= 0.0f)
        {
            this->velocity.y = -this->velocity.y;
            this->position.y = 0.0f;
        }

    }
    return this->position;
}

void BallObject::Reset(const glm::vec2 position, const glm::vec2 velocity) {
	this->position = position;
	this->velocity = velocity;
	this->stuck = true;
}
