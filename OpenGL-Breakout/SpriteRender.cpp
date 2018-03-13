#include "SpriteRender.h"
#include <Glm/gtc/matrix_transform.hpp>

SpriteRenderer::SpriteRenderer(Shader &&shader) : quadVao_(0) { this->shader_ = shader; this->InitRenderData(); }

SpriteRenderer::~SpriteRenderer() {
	glDeleteVertexArrays(1, &this->quadVao_);
}

void SpriteRenderer::DrawSprite(Texture2D& texture, const glm::vec2 position, const glm::vec2 size, const GLfloat rotate,
	const glm::vec3 color) {

	this->shader_.Use();
	glm::mat4 model(1.0f);
	model = translate(model, glm::vec3(position, 0.0f));
	model = translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));
	model = glm::rotate(model, rotate, glm::vec3(0.0f, 0.0f, 1.0f));
	model = translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));

	model = scale(model, glm::vec3(size, 1.0f));

	this->shader_.SetMatrix4("model", model);
	this->shader_.SetVector3F("spriteColor", color);

	glActiveTexture(GL_TEXTURE0);
	texture.Bind();
	glBindVertexArray(this->quadVao_);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);


}

void SpriteRenderer::InitRenderData() {
	GLuint vbo;
	GLfloat vertices[] = {
		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,

		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f
	};

	glGenVertexArrays(1, &this->quadVao_);
	glGenBuffers(1, &vbo);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindVertexArray(this->quadVao_);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), static_cast<GLvoid*>(0));
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);


}
