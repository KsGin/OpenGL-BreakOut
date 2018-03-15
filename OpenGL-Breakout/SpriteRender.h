#pragma once
#include "Shader.h"
#include "Texture2D.h"

class SpriteRenderer
{
    public:
	explicit SpriteRenderer(Shader &&shader);
        ~SpriteRenderer();

        void DrawSprite(Texture2D &texture, glm::vec2 position, 
            glm::vec2 size = glm::vec2(10, 10), GLfloat rotate = 0.0f, 
            glm::vec3 color = glm::vec3(0.1f));
    private:
        Shader shader_; 
        GLuint quadVao_;

        void InitRenderData();
};
